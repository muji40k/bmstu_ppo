#include "LogUserRequestManager.h"

LogUserRequestManager::LogUserRequestManager(std::shared_ptr<ILogger> logger,
                                 std::shared_ptr<UserRequestManager> manager)
    : logger(logger), manager(manager)
{
    if (nullptr == logger || nullptr == manager)
        throw CALL_EX(NullptrLogUserRequestManagerException);
}

std::list<UserMapper::Map> LogUserRequestManager::findHuman(std::string hash, const UserMapper::Map &data) const
try
{
    this->logger->write(ILogger::INFO, "User " + hash + " attempted to find personal information");
    std::list<UserMapper::Map> res = this->manager->findHuman(hash, data);
    this->logger->write(ILogger::INFO, "User " + hash + " successfully found information");

    return res;
}
catch (AllocationAppContextException &er)
{
    this->logger->write(ILogger::ERROR, std::string("User Request manager allocation error: ") + er.what());
    throw er;
}
catch (AllocationRepositoryContextException &er)
{
    this->logger->write(ILogger::ERROR, std::string("User Request manager allocation error: ") + er.what());
    throw er;
}
catch (NotAuthenticatedUserRequestManagerException &er)
{
    this->logger->write(ILogger::WARNING, "Unidentified attempt to found personal information with " + hash);
    throw er;
}
catch (NotAuthorizedUserRequestManagerException &er)
{
    this->logger->write(ILogger::WARNING, "Unauthorized attempt to found personal information by user " + hash);
    throw er;
}
catch (UnspecifiedDataUserRequestManagerException &er)
{
    auto iter = data.begin();
    std::string datastring = "{" + (*iter).first + ": " + (*iter).second;

    for (; data.end() != iter; ++iter)
        datastring += ", " + (*iter).first + ": " + (*iter).second;

    datastring += "}";

    this->logger->write(ILogger::WARNING, "Wrong query data was supplied by user " + hash);
    this->logger->write(ILogger::DEBUG, "Wrong data: " + datastring);

    throw er;
}
catch (EmptyDataUserRequestManagerException &er)
{
    this->logger->write(ILogger::WARNING, "Empty query data was supplied by user " + hash);
    throw er;
}
catch (CommonReadRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("User Request manager database access error: ") + er.what());
    throw er;
}
catch (CommonWriteRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("User Request manager database access error: ") + er.what());
    throw er;
}
catch (CommonTimeChangeableRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("User Request manager database access error: ") + er.what());
    throw er;
}

void LogUserRequestManager::setHuman(std::string hash, const UserMapper::Map &data) const
try
{
    this->logger->write(ILogger::INFO, "User " + hash + " attempted to request set of personal information");
    this->manager->setHuman(hash, data);
    this->logger->write(ILogger::INFO, "User " + hash + " successfully requested set of personal information");
}
catch (AllocationAppContextException &er)
{
    this->logger->write(ILogger::ERROR, std::string("User Request manager allocation error: ") + er.what());
    throw er;
}
catch (AllocationRepositoryContextException &er)
{
    this->logger->write(ILogger::ERROR, std::string("User Request manager allocation error: ") + er.what());
    throw er;
}
catch (NotAuthenticatedUserRequestManagerException &er)
{
    this->logger->write(ILogger::WARNING, "Unidentified attempt to found personal information with " + hash);
    throw er;
}
catch (NotAuthorizedUserRequestManagerException &er)
{
    this->logger->write(ILogger::WARNING, "Unauthorized attempt to found personal information by user " + hash);
    throw er;
}
catch (UnsuitableDataUserRequestManagerException &er)
{
    auto iter = data.begin();
    std::string datastring = "{" + (*iter).first + ": " + (*iter).second;

    for (; data.end() != iter; ++iter)
        datastring += ", " + (*iter).first + ": " + (*iter).second;

    datastring += "}";

    this->logger->write(ILogger::WARNING, "Wrong data was supplied by user " + hash);
    this->logger->write(ILogger::DEBUG, "Wrong data: " + datastring);

    throw er;
}
catch (NotFoundUserRequestManagerException &er)
{
    auto iter = data.begin();
    std::string datastring = "{" + (*iter).first + ": " + (*iter).second;

    for (; data.end() != iter; ++iter)
        datastring += ", " + (*iter).first + ": " + (*iter).second;

    datastring += "}";

    this->logger->write(ILogger::WARNING, "No human was found with data supplied by user " + hash);
    this->logger->write(ILogger::DEBUG, "Reqeust data: " + datastring);
    throw er;
}
catch (CommonReadRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("User Request manager database access error: ") + er.what());
    throw er;
}
catch (CommonWriteRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("User Request manager database access error: ") + er.what());
    throw er;
}
catch (CommonTimeChangeableRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("User Request manager database access error: ") + er.what());
    throw er;
}

