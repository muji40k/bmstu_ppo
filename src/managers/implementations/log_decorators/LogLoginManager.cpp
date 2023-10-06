#include "LogLoginManager.h"

LogLoginManager::LogLoginManager(std::shared_ptr<ILogger> logger,
                                 std::shared_ptr<LoginManager> manager)
    : logger(logger), manager(manager)
{
    if (nullptr == logger || nullptr == manager)
        throw CALL_EX(NullptrLogLoginManagerException);
}

std::string LogLoginManager::login(std::string email, std::string password)
try
{
    this->logger->write(ILogger::INFO, "Login attempt for user " + email);
    std::string out = this->manager->login(email, password);
    this->logger->write(ILogger::INFO, "Successful login for user " + email + " hash: " + out);

    return out;
}
catch (AllocationRepositoryContextException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Login manager allocation error: ") + er.what());
    throw er;
}
catch (WrongLoginException &er)
{
    this->logger->write(ILogger::WARNING, "Unsuccessful login attempt for user " + email);
    throw er;
}
catch (AlreadyLoggedinException &er)
{
    this->logger->write(ILogger::WARNING, "Duplicate login for user " + email);
    throw er;
}
catch (CommonReadRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Login database access error: ") + er.what());
    throw er;
}

void LogLoginManager::registerUser(User user)
try
{
    this->logger->write(ILogger::INFO, "Register attempt with email " + *user.email);
    this->manager->registerUser(user);
    this->logger->write(ILogger::INFO, "Successful register for user " + *user.email);
}
catch (AllocationRepositoryContextException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Login manager allocation error: ") + er.what());
    throw er;
}
catch (AlreadyRegisteredException &er)
{
    this->logger->write(ILogger::WARNING, "User with email " + *user.email + " already exists");
    throw er;
}
catch (CommonReadRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Register database access error: ") + er.what());
    throw er;
}
catch (CommonWriteRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Register database access error: ") + er.what());
    throw er;
}

std::string LogLoginManager::update(std::string hash)
try
{
    this->logger->write(ILogger::INFO, "Update attempt for user " + hash);
    std::string out = this->manager->update(hash);
    this->logger->write(ILogger::INFO, "Successful update for user " + hash + ", updated value " + out);

    return out;
}
catch (AllocationRepositoryContextException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Login manager allocation error: ") + er.what());
    throw er;
}
catch (NotAuthenticatedException &er)
{
    this->logger->write(ILogger::WARNING, "Unauthorized attempt to update with hash " + hash);
    throw er;
}
catch (NoUserException &er)
{
    this->logger->write(ILogger::WARNING, "Update attempt for deleted user " + hash);
    throw er;
}
catch (AlreadyLoggedinException &er)
{
    this->logger->write(ILogger::WARNING, "Updated user already authenticated " + hash);
    throw er;
}
catch (CommonReadRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Update database access error: ") + er.what());
    throw er;
}

void LogLoginManager::exit(std::string hash)
{
    this->logger->write(ILogger::INFO, "Exit attempt for user " + hash);
    this->manager->exit(hash);
}

bool LogLoginManager::isAuthenticated(std::string hash) const
{
    this->logger->write(ILogger::INFO, "User " + hash + " check authentication");

    return this->manager->isAuthenticated(hash);
}

const User &LogLoginManager::getAuthenticated(std::string hash) const
try
{
    this->logger->write(ILogger::INFO, "User " + hash + " tries to get profile data");
    const User &out = this->manager->getAuthenticated(hash);
    this->logger->write(ILogger::INFO, "Profile data was retrieved by user " + hash);

    return out;
}
catch (NotAuthenticatedException &er)
{
    this->logger->write(ILogger::WARNING, "Unidentified user " + hash + " tried to get get profile data");
    throw er;
}

