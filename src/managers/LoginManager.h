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
        LoginManager(RepositoryContext &context, HashFunc func,
                     std::shared_ptr<RegistrationHook> hook = nullptr);
        virtual ~LoginManager(void) = default;

        virtual std::string login(std::string email, std::string password);
        virtual void registerUser(User user);
        virtual std::string update(std::string hash);
        virtual void exit(std::string hash);
        virtual bool isAuthenticated(std::string hash) const;
        virtual const User &getAuthenticated(std::string hash) const;

    private:
        RepositoryContext &context;
        HashFunc hash;
        std::shared_ptr<RegistrationHook> hook = nullptr;
        std::unordered_map<std::string, User> authenticated;
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

