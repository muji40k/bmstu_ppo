#include "LogQueryManager.h"

LogQueryManager::LogQueryManager(std::shared_ptr<ILogger> logger,
                                 std::shared_ptr<QueryManager> manager)
    : logger(logger), manager(manager)
{
    if (nullptr == logger || nullptr == manager)
        throw CALL_EX(NullptrLogQueryManagerException);
}

void LogQueryManager::find(IQueryStrategy &strategy)
try
{
    this->manager->find(strategy);
}
catch (AllocationAppContextException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Query manager allocation error: ") + er.what());
    throw er;
}
catch (AllocationRepositoryContextException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Query manager allocation error: ") + er.what());
    throw er;
}
catch (CommonIQueryStrategyException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Query manager strategy error: ") + er.what());
    throw er;
}
catch (CommonTimeChangeableRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Query manager database access error: ") + er.what());
    throw er;
}

