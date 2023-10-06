#include "LogUserInfoManager.h"

LogUserInfoManager::LogUserInfoManager(std::shared_ptr<ILogger> logger,
                                 std::shared_ptr<UserInfoManager> manager)
    : logger(logger), manager(manager)
{
    if (nullptr == logger || nullptr == manager)
        throw CALL_EX(NullptrLogUserInfoManagerException);
}

UserMapper::Map LogUserInfoManager::getInfo(std::string hash) const
try
{
    this->logger->write(ILogger::INFO, "User " + hash + " attempted to get profile info");
    UserMapper::Map out = this->manager->getInfo(hash);
    this->logger->write(ILogger::INFO, "User " + hash + " successfully got profile info");

    return out;
}
catch (AllocationAppContextException &er)
{
    this->logger->write(ILogger::ERROR, std::string("User Info manager allocation error: ") + er.what());
    throw er;
}
catch (AllocationRepositoryContextException &er)
{
    this->logger->write(ILogger::ERROR, std::string("User Info manager allocation error: ") + er.what());
    throw er;
}
catch (NotAuthenticatedUserInfoManagerException &er)
{
    this->logger->write(ILogger::WARNING, "Unidentified attempt to get profile with " + hash);
    throw er;
}
catch (NotAuthorizedUserInfoManagerException &er)
{
    this->logger->write(ILogger::WARNING, "Unauthorized attempt to get profile by user " + hash);
    throw er;
}
catch (CommonReadRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("User Info manager database access error: ") + er.what());
    throw er;
}

void LogUserInfoManager::updateInfo(std::string hash, const UserMapper::Map &map)
try
{
    this->logger->write(ILogger::INFO, "User " + hash + " attempted to update profile info");
    UserMapper::Map out = this->manager->getInfo(hash);
    this->logger->write(ILogger::INFO, "User " + hash + " successfully updated profile info");
}
catch (AllocationAppContextException &er)
{
    this->logger->write(ILogger::ERROR, std::string("User Info manager allocation error: ") + er.what());
    throw er;
}
catch (AllocationRepositoryContextException &er)
{
    this->logger->write(ILogger::ERROR, std::string("User Info manager allocation error: ") + er.what());
    throw er;
}
catch (NotAuthenticatedUserInfoManagerException &er)
{
    this->logger->write(ILogger::WARNING, "Unidentified attempt to update profile with " + hash);
    throw er;
}
catch (NotAuthorizedUserInfoManagerException &er)
{
    this->logger->write(ILogger::WARNING, "Unauthorized attempt to update profile by user " + hash);
    throw er;
}
catch (UnexpectedKeyUserInfoManagerException &er)
{
    auto iter = map.begin();
    std::string mapstring = "{" + (*iter).first + ": " + (*iter).second;

    for (; map.end() != iter; ++iter)
        mapstring += ", " + (*iter).first + ": " + (*iter).second;

    mapstring += "}";

    this->logger->write(ILogger::WARNING, "Wrong profile data was supplied by user " + hash);
    this->logger->write(ILogger::DEBUG, "Wrong data: " + mapstring);
    throw er;
}
catch (CommonReadRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("User Info manager database access error: ") + er.what());
    throw er;
}
catch (CommonWriteRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("User Info manager database access error: ") + er.what());
    throw er;
}

bool LogUserInfoManager::isHuman(std::string hash) const
try
{
    this->logger->write(ILogger::INFO, "User " + hash + " attempted to check his human record");
    bool res = this->manager->isHuman(hash);
    this->logger->write(ILogger::INFO, "User " + hash + " successfully checked his human record");

    return res;
}
catch (AllocationAppContextException &er)
{
    this->logger->write(ILogger::ERROR, std::string("User Info manager allocation error: ") + er.what());
    throw er;
}
catch (AllocationRepositoryContextException &er)
{
    this->logger->write(ILogger::ERROR, std::string("User Info manager allocation error: ") + er.what());
    throw er;
}
catch (NotAuthenticatedUserInfoManagerException &er)
{
    this->logger->write(ILogger::WARNING, "Unidentified attempt to check human with " + hash);
    throw er;
}
catch (NotAuthorizedUserInfoManagerException &er)
{
    this->logger->write(ILogger::WARNING, "Unauthorized attempt to check human by user " + hash);
    throw er;
}
catch (CommonReadRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("User Info manager database access error: ") + er.what());
    throw er;
}
catch (CommonWriteRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("User Info manager database access error: ") + er.what());
    throw er;
}
catch (CommonTimeChangeableRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("User Info manager database access error: ") + er.what());
    throw er;
}

UserMapper::Map LogUserInfoManager::getHuman(std::string hash) const
try
{
    this->logger->write(ILogger::INFO, "User " + hash + " attempted to get human record");
    UserMapper::Map res = this->manager->getHuman(hash);
    this->logger->write(ILogger::INFO, "User " + hash + " successfully got human record");

    return res;
}
catch (AllocationAppContextException &er)
{
    this->logger->write(ILogger::ERROR, std::string("User Info manager allocation error: ") + er.what());
    throw er;
}
catch (AllocationRepositoryContextException &er)
{
    this->logger->write(ILogger::ERROR, std::string("User Info manager allocation error: ") + er.what());
    throw er;
}
catch (NotAuthenticatedUserInfoManagerException &er)
{
    this->logger->write(ILogger::WARNING, "Unidentified attempt to get human with " + hash);
    throw er;
}
catch (NotAuthorizedUserInfoManagerException &er)
{
    this->logger->write(ILogger::WARNING, "Unauthorized attempt to get human by user " + hash);
    throw er;
}
catch (CommonReadRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("User Info manager database access error: ") + er.what());
    throw er;
}
catch (CommonWriteRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("User Info manager database access error: ") + er.what());
    throw er;
}
catch (CommonTimeChangeableRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("User Info manager database access error: ") + er.what());
    throw er;
}

