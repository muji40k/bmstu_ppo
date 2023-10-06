#include "PlainAdminInfoManager.h"

#include "LoginManager.h"
#include "AuthorizationManager.h"

PlainAdminInfoManager::PlainAdminInfoManager(AppContext &context)
    : context(context)
{}

void PlainAdminInfoManager::process(std::string hash, AdminInfoStrategy &strategy)
{
    auto login = this->context.getLoginManager();

    if (!login->isAuthenticated(hash))
        throw CALL_EX(NotAuthenticatedAdminInfoManagerException);

    auto authorizator = this->context.getAuthorizationManager();

    if (!authorizator->authorize(hash, {"admin"}))
        throw CALL_EX(NotAuthorizedAdminInfoManagerException);

    strategy.apply(this->context);
}

