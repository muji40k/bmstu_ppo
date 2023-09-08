#include "AdminInfoManager.h"

#include "LoginManager.h"
#include "AuthorizationManager.h"

AdminInfoManager::AdminInfoManager(AppContext &context)
    : context(context)
{}

void AdminInfoManager::process(std::string hash, AdminInfoStrategy &strategy)
{
    auto login = this->context.getLoginManager();

    if (!login->isAuthenticated(hash))
        throw CALL_EX(NotAuthenticatedAdminInfoManagerException);

    const User user = login->getAuthenticated(hash);
    auto authorizator = this->context.getAuthorizationManager();

    if (!authorizator->authorize(user, {"admin"}))
        throw CALL_EX(NotAuthorizedAdminInfoManagerException);

    strategy.apply(this->context);
}

