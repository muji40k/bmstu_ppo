#include "PlainAdminRequestManager.h"

#include <cctype>
#include <algorithm>

#include "typestring.h"

#include "ValueCriteria.h"

#include "LoginManager.h"
#include "AuthorizationManager.h"

PlainAdminRequestManager::PlainAdminRequestManager(AppContext &context, RequestHandlerSet &handler)
    : context(context), handler(handler)
{}

RequestSet PlainAdminRequestManager::getRequests(std::string hash)
{
    auto login = this->context.getLoginManager();

    if (!login->isAuthenticated(hash))
        throw CALL_EX(NotAuthenticatedAdminRequestManagerException);

    const User user = login->getAuthenticated(hash);
    auto authorizator = this->context.getAuthorizationManager();

    if (!authorizator->authorize(hash, {"admin"}))
        throw CALL_EX(NotAuthorizedAdminRequestManagerException);

    auto repo = this->context.getRepositoryContext().getMergeRequestRepository();
    ValueCriteria new_criteria (TypeName::getAttribute<MergeRequest>("state"), "=", "new");

    return RequestSet(repo->get(new_criteria));
}

void PlainAdminRequestManager::updateRequest(std::string hash, const MergeRequest &request)
{
    auto login = this->context.getLoginManager();

    if (!login->isAuthenticated(hash))
        throw CALL_EX(NotAuthenticatedAdminRequestManagerException);

    auto authorizator = this->context.getAuthorizationManager();

    if (!authorizator->authorize(hash, {"admin"}))
        throw CALL_EX(NotAuthorizedAdminRequestManagerException);

    try
    {
        this->handler.handle(this->context, request);
    }
    catch (NoHandlerRequestHandlerSetException &)
    {
        throw CALL_EX(NoHandlerAdminRequestManagerException);
    }

    auto repo = this->context.getRepositoryContext().getMergeRequestRepository();
    repo->update(request);
}

