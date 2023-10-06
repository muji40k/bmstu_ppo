#ifndef _LOGINMANAGER_H_
#define _LOGINMANAGER_H_

#include <memory>
#include <unordered_map>
#include <string>
#include <list>

#include "manager_exceptions.h"

#include "RepositoryContext.h"
#include "User.h"
#include "RegistrationHook.h"

class LoginManager
{
    public:
        using HashFunc = std::string (*)(const User &user);

    public:
        virtual ~LoginManager(void) = default;

        virtual std::string login(std::string email, std::string password) = 0;
        virtual void registerUser(User user) = 0;
        virtual std::string update(std::string hash) = 0;
        virtual void exit(std::string hash) = 0;
        virtual bool isAuthenticated(std::string hash) const = 0;
        virtual const User &getAuthenticated(std::string hash) const = 0;
};

DEF_EX(CommonLoginManagerException, ManagerException,
       "Common LoginManager exception");
DEF_EX(HashFuncNotSetException, CommonLoginManagerException,
       "Passed hash function referenced by nullptr");
DEF_EX(WrongLoginException, CommonLoginManagerException,
       "Incorrect login");
DEF_EX(AlreadyLoggedinException, CommonLoginManagerException,
       "User already authenticated");
DEF_EX(AlreadyRegisteredException, CommonLoginManagerException,
       "User already registered");
DEF_EX(NotAuthenticatedException, CommonLoginManagerException,
       "Hash doesn't specify any authenticated user");
DEF_EX(NoUserException, CommonLoginManagerException,
       "User doesn't exist");

#endif

