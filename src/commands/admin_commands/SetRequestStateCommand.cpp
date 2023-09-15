#include "SetRequestStateCommand.h"

#include "AdminRequestManager.h"

SetRequestStateCommand::SetRequestStateCommand(const std::string hash, const MergeRequest mr)
    : hash(hash), mr(mr)
{}

void SetRequestStateCommand::execute(AppContext &context)
try
{
    std::shared_ptr<AdminRequestManager> manager = context.getAdminRequestManager();
    manager->updateRequest(this->hash, this->mr);
}
catch (AllocationAppContextException &)
{
    throw CALL_EX(AllocationSetRequestStateCommandException);
}
catch (AllocationRepositoryContextException &)
{
    throw CALL_EX(AllocationSetRequestStateCommandException);
}
catch (NotAuthenticatedAdminRequestManagerException &)
{
    throw CALL_EX(NotAuthenticatedSetRequestStateCommandException);
}
catch (NotAuthorizedAdminRequestManagerException &)
{
    throw CALL_EX(NotAuthorizedSetRequestStateCommandException);
}
catch (CommonReadRepositoryException &er)
{
    throw CALL_EX_MSG(RepositorySetRequestStateCommandException, er.what());
}
catch (CommonWriteRepositoryException &er)
{
    throw CALL_EX_MSG(RepositorySetRequestStateCommandException, er.what());
}
catch (CommonTimeChangeableRepositoryException &er)
{
    throw CALL_EX_MSG(RepositorySetRequestStateCommandException, er.what());
}

