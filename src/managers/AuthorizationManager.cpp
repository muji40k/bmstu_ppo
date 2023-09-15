#include "AuthorizationManager.h"

#include <list>

#include "typestring.h"

#include "LogicCriteriaBuilder.h"
#include "ValueCriteria.h"

AuthorizationManager::AuthorizationManager(RepositoryContext &context)
    : context(context)
{}

bool AuthorizationManager::authorize(const User &user,
                                     std::initializer_list<std::string> roles)
{
    return this->innerAuthorize<std::initializer_list<std::string>>(user, roles);
}

bool AuthorizationManager::authorize(const User &user,
                                     std::list<std::string> roles)
{
    return this->innerAuthorize<std::list<std::string>>(user, roles);
}

template <typename Container>
bool AuthorizationManager::innerAuthorize(const User &user,
                                          const Container &container)
{
    if (0 == container.size())
        throw CALL_EX(EmptyListException);

    std::shared_ptr<IUserRoleRepository> repo = this->context.getUserRoleRepository();

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

