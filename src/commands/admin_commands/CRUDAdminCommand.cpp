#include "CRUDAdminCommand.h"

CRUDAdminCommand::CRUDAdminCommand(const std::string hash, AdminInfoStrategy &strategy)
    : hash(hash), strategy(strategy)
{}

void CRUDAdminCommand::execute(AppContext &context)
try
{
    std::shared_ptr<AdminInfoManager> manager = context.getAdminInfoManager();
    manager->process(this->hash, this->strategy);
}
catch (AllocationAppContextException &)
{
    throw CALL_EX(AllocationCRUDAdminCommandException);
}
catch (AllocationRepositoryContextException &)
{
    throw CALL_EX(AllocationCRUDAdminCommandException);
}
catch (NotAuthenticatedAdminInfoManagerException &)
{
    throw CALL_EX(NotAuthenticatedCRUDAdminCommandException);
}
catch (NotAuthorizedAdminInfoManagerException &)
{
    throw CALL_EX(NotAuthorizedCRUDAdminCommandException);
}
catch (CommonAdminInfoStrategyException &er)
{
    throw CALL_EX_MSG(StrategyCRUDAdminCommandException, er.what());
}
catch (CommonReadRepositoryException &er)
{
    throw CALL_EX_MSG(RepositoryCRUDAdminCommandException, er.what());
}
catch (CommonWriteRepositoryException &er)
{
    throw CALL_EX_MSG(RepositoryCRUDAdminCommandException, er.what());
}
catch (CommonTimeChangeableRepositoryException &er)
{
    throw CALL_EX_MSG(RepositoryCRUDAdminCommandException, er.what());
}

