#include "LogAdminInfoManager.h"

LogAdminInfoManager::LogAdminInfoManager(std::shared_ptr<ILogger> logger,
                                 std::shared_ptr<AdminInfoManager> manager)
    : logger(logger), manager(manager)
{
    if (nullptr == logger || nullptr == manager)
        throw CALL_EX(NullptrLogAdminInfoManagerException);
}

void LogAdminInfoManager::process(std::string hash, AdminInfoStrategy &strategy)
try
{
    this->logger->write(ILogger::INFO, "User " + hash + " attempted to execute admin query");
    this->manager->process(hash, strategy);
    this->logger->write(ILogger::INFO, "User " + hash + " successfully executed admin query");
}
catch (AllocationAppContextException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Admin query allocation error: ") + er.what());
    throw er;
}
catch (AllocationRepositoryContextException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Admin query allocation error: ") + er.what());
    throw er;
}
catch (NotAuthenticatedAdminInfoManagerException &er)
{
    this->logger->write(ILogger::WARNING, "Unidentified attempt to execute admin query with " + hash);
    throw er;
}
catch (NotAuthorizedAdminInfoManagerException &er)
{
    this->logger->write(ILogger::WARNING, "Unauthorized attempt to execute admin query by user " + hash);
    throw er;
}
catch (CommonAdminInfoStrategyException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Admin query error: ") + er.what());
    throw er;
}
catch (CommonReadRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Admin query database access error: ") + er.what());
    throw er;
}
catch (CommonWriteRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Admin query database access error: ") + er.what());
    throw er;
}
catch (CommonTimeChangeableRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Admin query database access error: ") + er.what());
    throw er;
}

