#include "IsAdminCommand.h"

#include "LoginManager.h"
#include "AuthorizationManager.h"

IsAdminCommand::IsAdminCommand(const std::string hash)
    : hash(hash)
{}

void IsAdminCommand::execute(AppContext &context)
try
{
    std::shared_ptr<LoginManager> login = context.getLoginManager();
    std::shared_ptr<AuthorizationManager> authorizer = context.getAuthorizationManager();

    if (!login->isAuthenticated(this->hash))
        throw CALL_EX(NotAuthenticatedIsAdminCommandException);

    static const std::list<std::string> roles = {"admin"};
    this->res = authorizer->authorize(this->hash, roles);
}
catch (AllocationAppContextException &er)
{
    throw CALL_EX_MSG(AllocationIsAdminCommandException, er.what());
}
catch (CommonReadRepositoryException &er)
{
    throw CALL_EX_MSG(RepositoryIsAdminCommandException, er.what());
}

const bool &IsAdminCommand::result(void)
{
    return this->res;
}
