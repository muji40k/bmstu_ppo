#include "LogAuthorizationManager.h"

LogAuthorizationManager::LogAuthorizationManager(std::shared_ptr<ILogger> logger,
                                 std::shared_ptr<AuthorizationManager> manager)
    : logger(logger), manager(manager)
{
    if (nullptr == logger || nullptr == manager)
        throw CALL_EX(NullptrLogAuthorizationManagerException);
}

template <typename Container>
bool LogAuthorizationManager::innerAuthorize(const std::string &hash,
                    const Container &container)
try
{
    auto iter = container.begin();
    std::string roles = *iter++;

    for (; container.end() != iter; ++iter)
        roles += ", " + *iter;

    this->logger->write(ILogger::INFO, "User " + hash + " attempted to authorize roles: " + roles);
    bool res = this->manager->authorize(hash, container);
    this->logger->write(ILogger::INFO, "User " + hash + " successfully authorized");

    return res;
}
catch (AllocationAppContextException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Authorization manager allocation error: ") + er.what());
    throw er;
}
catch (AllocationRepositoryContextException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Authorization manager allocation error: ") + er.what());
    throw er;
}
catch (NotAuthenticatedAuthorizationManagerException &er)
{
    this->logger->write(ILogger::WARNING, "Unidentified attempt to get roles with " + hash);
    throw er;
}
catch (CommonReadRepositoryException &er)
{
    this->logger->write(ILogger::ERROR, std::string("Authorization manager database access error: ") + er.what());
    throw er;
}

bool LogAuthorizationManager::authorize(const std::string &hash,
                       std::initializer_list<std::string> roles)
{
    return this->innerAuthorize(hash, roles);
}

bool LogAuthorizationManager::authorize(const std::string &hash,
                       std::list<std::string> roles)
{
    return this->innerAuthorize(hash, roles);
}

