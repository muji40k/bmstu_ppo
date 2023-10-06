#include <PlainLoginManager.h>

#include <utility>

#include "typestring.h"

#include "ValueCriteria.h"

PlainLoginManager::PlainLoginManager(RepositoryContext &context, HashFunc func,
                           std::shared_ptr<RegistrationHook> hook)
    : context(context), hash(func), hook(hook)
{
    if (nullptr == func)
        throw CALL_EX(HashFuncNotSetException);
}

std::string PlainLoginManager::login(std::string email, std::string password)
{
    std::shared_ptr<IUserRepository> user_repo = this->context.getUserRepository();

    ValueCriteria email_criteria (TypeName::getAttribute<User>("email"), "=", email);
    auto set = user_repo->get(email_criteria);
    auto iter = set->begin();

    if (!set->end()->notEqual(iter))
        throw CALL_EX(WrongLoginException);

    const User user = iter->get();

    if (user.password != password)
        throw CALL_EX(WrongLoginException);

    std::string hash = this->hash(user);

    if (this->isAuthenticated(hash))
        throw CALL_EX(AlreadyLoggedinException);

    this->authenticated.emplace(std::pair(hash, user));

    return hash;
}

void PlainLoginManager::registerUser(User user)
{
    std::shared_ptr<IUserRepository> user_repo = this->context.getUserRepository();

    ValueCriteria email_criteria (TypeName::getAttribute<User>("email"), "=", user.email);
    auto set = user_repo->get(email_criteria);
    auto iter = set->begin();

    if (set->end()->notEqual(iter))
        throw CALL_EX(AlreadyRegisteredException);

    user_repo->create(user);

    if (nullptr != this->hook)
    {
        set = user_repo->get(email_criteria);
        user = set->begin()->get();
        this->hook->perform(this->context, user);
    }
}

std::string PlainLoginManager::update(std::string hash)
{
    if (!this->isAuthenticated(hash))
        throw CALL_EX(NotAuthenticatedException);

    auto iter = this->authenticated.find(hash);
    User user = iter->second;

    std::shared_ptr<IUserRepository> repo = this->context.getUserRepository();

    ValueCriteria criteria (TypeName::getAttribute<User>("id"), "=", std::to_string(user.id));
    auto set = repo->get(criteria);
    auto uiter = set->begin();

    if (!set->end()->notEqual(uiter))
        throw CALL_EX(NoUserException);

    user = uiter->get();
    std::string new_hash = this->hash(user);

    if (hash == new_hash)
        return hash;

    this->authenticated.erase(iter);

    if (this->isAuthenticated(new_hash))
        throw CALL_EX(AlreadyLoggedinException);

    this->authenticated.emplace(std::pair(new_hash, user));

    return new_hash;
}

void PlainLoginManager::exit(std::string hash)
{
    this->authenticated.erase(hash);
}

bool PlainLoginManager::isAuthenticated(std::string hash) const
{
    auto iter = this->authenticated.find(hash);

    if (this->authenticated.end() == iter)
        return false;

    return true;
}

const User &PlainLoginManager::getAuthenticated(std::string hash) const
{
    if (!this->isAuthenticated(hash))
        throw CALL_EX(NotAuthenticatedException);

    return this->authenticated.at(hash);
}

