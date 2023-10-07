#include "GetRequestsCommand.h"

GetRequestsCommand::GetRequestsCommand(const std::string hash)
    : hash(hash)
{}

void GetRequestsCommand::execute(AppContext &context)
try
{
    std::shared_ptr<AdminRequestManager> manager = context.getAdminRequestManager();
    this->set = std::make_shared<RequestSet>(manager->getRequests(this->hash));
}
catch (AllocationAppContextException &)
{
    throw CALL_EX(AllocationGetRequestsCommandException);
}
catch (AllocationRepositoryContextException &)
{
    throw CALL_EX(AllocationGetRequestsCommandException);
}
catch (NotAuthenticatedAdminRequestManagerException &)
{
    throw CALL_EX(NotAuthenticatedGetRequestsCommandException);
}
catch (NotAuthorizedAdminRequestManagerException &)
{
    throw CALL_EX(NotAuthorizedGetRequestsCommandException);
}
catch (CommonReadRepositoryException &er)
{
    throw CALL_EX_MSG(RepositoryGetRequestsCommandException, er.what());
}
catch (CommonWriteRepositoryException &er)
{
    throw CALL_EX_MSG(RepositoryGetRequestsCommandException, er.what());
}
catch (CommonTimeChangeableRepositoryException &er)
{
    throw CALL_EX_MSG(RepositoryGetRequestsCommandException, er.what());
}

const RequestSet &GetRequestsCommand::result(void)
{
    if (nullptr == this->set)
        throw CALL_EX(NotPrerformedGetRequestsCommandException);

    return *this->set;
}

