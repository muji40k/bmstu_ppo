#include "AdminRequestManager.h"

#include <cctype>
#include <algorithm>

#include "typestring.h"

#include "ValueCriteria.h"

#include "LoginManager.h"
#include "AuthorizationManager.h"

RequestSetIterator::RequestSetIterator(std::shared_ptr<IRepositoryIterator<MergeRequest>> iter)
    : iter(iter)
{
    if (nullptr == iter)
        throw CALL_EX(NullptrRequestSetIteratorException);
}

MergeRequest RequestSetIterator::operator * (void) const
{
    return this->iter->get();
}

RequestSetIterator &RequestSetIterator::operator ++ (int)
{
    this->iter->next();

    return *this;
}

bool RequestSetIterator::operator != (const RequestSetIterator &iter)
{
    return this->iter->notEqual(iter.iter);
}

RequestSet::RequestSet(std::shared_ptr<IRepositorySet<MergeRequest>> set)
    : requests(set)
{
    if (nullptr == set)
        throw CALL_EX(NullptrRequestSetException);
}

RequestSetIterator RequestSet::begin(void)
{
    if (nullptr == this->b)
        this->b = this->requests->begin();

    return RequestSetIterator(this->b);
}

RequestSetIterator RequestSet::end(void)
{
    if (nullptr == this->e)
        this->e = this->requests->end();

    return RequestSetIterator(this->e);
}

AdminRequestManager::AdminRequestManager(AppContext &context, RequestHandlerSet &handler)
    : context(context), handler(handler)
{}

 RequestSet AdminRequestManager::getRequests(std::string hash)
{
    auto login = this->context.getLoginManager();

    if (!login->isAuthenticated(hash))
        throw CALL_EX(NotAuthenticatedAdminRequestManagerException);

    const User user = login->getAuthenticated(hash);
    auto authorizator = this->context.getAuthorizationManager();

    if (!authorizator->authorize(user, {"admin"}))
        throw CALL_EX(NotAuthorizedAdminRequestManagerException);

    auto repo = this->context.getRepositoryContext().getMergeRequestRepository();
    ValueCriteria new_criteria (TypeName::getAttribute<MergeRequest>("state"), "=", "new");

    return RequestSet(repo->get(new_criteria));
}

void AdminRequestManager::updateRequest(std::string hash, const MergeRequest &request)
{
    auto login = this->context.getLoginManager();

    if (!login->isAuthenticated(hash))
        throw CALL_EX(NotAuthenticatedAdminRequestManagerException);

    const User user = login->getAuthenticated(hash);
    auto authorizator = this->context.getAuthorizationManager();

    if (!authorizator->authorize(user, {"admin"}))
        throw CALL_EX(NotAuthorizedAdminRequestManagerException);

    this->handler.handle(this->context, request);

    auto repo = this->context.getRepositoryContext().getMergeRequestRepository();
    repo->update(request);
}

