#include "AuthorizationManager.h"

#include <list>

#include "typestring.h"

#include "LoginManager.h"

#include "LogicCriteriaBuilder.h"
#include "ValueCriteria.h"

AuthorizationManager::AuthorizationManager(AppContext &context,
                                           std::shared_ptr<AuthorizationHook> hook)
    : context(context), hook(hook)
{}

bool AuthorizationManager::authorize(const std::string &hash,
                                     std::initializer_list<std::string> roles)
{
    return this->innerAuthorize<std::initializer_list<std::string>>(hash, roles);
}

bool AuthorizationManager::authorize(const std::string &hash,
                                     std::list<std::string> roles)
{
    return this->innerAuthorize<std::list<std::string>>(hash, roles);
}

template <typename Container>
bool AuthorizationManager::innerAuthorize(const std::string &hash,
                                          const Container &container)
{
    if (0 == container.size())
        throw CALL_EX(EmptyListException);

    auto login = this->context.getLoginManager();

    if (!login->isAuthenticated(hash))
        throw CALL_EX(NotAuthenticatedAuthorizationManagerException);

    User user = login->getAuthenticated(hash);

    if (this->hook)
        return this->hook->perform(this->context.getRepositoryContext(), user, container);

    std::shared_ptr<IUserRoleRepository> repo = this->context.getRepositoryContext().getUserRoleRepository();

    LogicCriteriaBuilder builder (std::make_shared<ValueCriteria>(TypeName::getAttribute<UserRole>("userId"), "=", std::to_string(user.id)));
    auto iter = container.begin();
    builder.addAND(std::make_shared<ValueCriteria>(TypeName::getAttribute<UserRole>("role"), "=", *iter));

    while (container.end() != ++iter)
        builder.addOR(std::make_shared<ValueCriteria>(TypeName::getAttribute<UserRole>("role"), "=", *iter));

    auto set = repo->get(*builder.get());

    if (set->end()->notEqual(set->begin()))
        return true;

    return false;
}

