#include <LoginManager.h>

#include <utility>

#include "typestring.h"

#include "ValueCriteria.h"

LoginManager::LoginManager(RepositoryContext &context,
                           LoginManager::HashFunc func)
    : context(context), hash(func)
{
    if (nullptr == func)
        throw CALL_EX(HashFuncNotSetException);
}

std::string LoginManager::login(std::string email, std::string password)
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

void LoginManager::registerUser(User user)
{
    std::shared_ptr<IUserRepository> user_repo = this->context.getUserRepository();

    ValueCriteria email_criteria (TypeName::getAttribute<User>("email"), "=", user.email);
    auto set = user_repo->get(email_criteria);
    auto iter = set->begin();

    if (set->end()->notEqual(iter))
        throw CALL_EX(AlreadyRegisteredException);

    user_repo->create(user);
}

std::string LoginManager::update(std::string hash)
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

void LoginManager::exit(std::string hash)
{
    this->authenticated.erase(hash);
}

bool LoginManager::isAuthenticated(std::string hash) const
{
    auto iter = this->authenticated.find(hash);

    if (this->authenticated.end() == iter)
        return false;

    return true;
}

const User &LoginManager::getAuthenticated(std::string hash) const
{
    if (!this->isAuthenticated(hash))
        throw CALL_EX(NotAuthenticatedException);

    return this->authenticated.at(hash);
}
