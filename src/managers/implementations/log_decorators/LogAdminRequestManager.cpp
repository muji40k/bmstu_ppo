#include "LogAdminRequestManager.h"

LogAdminRequestManager::LogAdminRequestManager(std::shared_ptr<ILogger> logger,
                                 std::shared_ptr<AdminRequestManager> manager)
    : logger(logger), manager(manager)
{
    if (nullptr == logger || nullptr == manager)
        throw CALL_EX(NullptrLogAdminRequestManagerException);
}

RequestSet LogAdminRequestManager::getRequests(std::string hash)
try
{
    this->logger->write(ILogger::INFO, "User " + hash + " attempted to get merge requests");
    RequestSet out = this->manager->getRequests(hash);
    this->logger->write(ILogger::INFO, "User " + hash + " successfully got merge requests");

    return out;
}
catch (AllocationAppContextException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Merge requests manager allocation error: ") + er.what());
    throw er;
}
catch (AllocationRepositoryContextException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Merge requests manager allocation error: ") + er.what());
    throw er;
}
catch (NotAuthenticatedAdminRequestManagerException &er)
{
    this->logger->write(ILogger::WARNING, "Unidentified attempt to get merge requests with " + hash);
    throw er;
}
catch (NotAuthorizedAdminRequestManagerException &er)
{
    this->logger->write(ILogger::WARNING, "Unauthorized attempt to get merge requests by user " + hash);
    throw er;
}
catch (CommonReadRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Merge requests database access error: ") + er.what());
    throw er;
}
catch (CommonWriteRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Merge requests database access error: ") + er.what());
    throw er;
}
catch (CommonTimeChangeableRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Merge requests database access error: ") + er.what());
    throw er;
}

void LogAdminRequestManager::updateRequest(std::string hash, const MergeRequest &request)
try
{
    this->logger->write(ILogger::INFO, "User " + hash + " attempted to update merge request " + std::to_string(*request.id));
    this->manager->updateRequest(hash, request);
    this->logger->write(ILogger::INFO, "User " + hash + " successfully updated merge request " + std::to_string(*request.id));
}
catch (AllocationAppContextException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Merge requests manager allocation error: ") + er.what());
    throw er;
}
catch (AllocationRepositoryContextException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Merge requests manager allocation error: ") + er.what());
    throw er;
}
catch (NotAuthenticatedAdminRequestManagerException &er)
{
    this->logger->write(ILogger::WARNING, "Unidentified attempt to set merge requests with " + hash);
    throw er;
}
catch (NotAuthorizedAdminRequestManagerException &er)
{
    this->logger->write(ILogger::WARNING, "Unauthorized attempt to set merge requests by user " + hash);
    throw er;
}
catch (NoHandlerAdminRequestManagerException &er)
{
    this->logger->write(ILogger::WARNING, "Attempt to set state " + *request.state + " for merge request " + std::to_string(*request.id) + " by user " + hash);
    throw er;
}
catch (CommonReadRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Merge requests database access error: ") + er.what());
    throw er;
}
catch (CommonWriteRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Merge requests database access error: ") + er.what());
    throw er;
}
catch (CommonTimeChangeableRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Merge requests database access error: ") + er.what());
    throw er;
}

