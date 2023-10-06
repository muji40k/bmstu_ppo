#ifndef _AUTHORIZATIONMANAGER_H_
#define _AUTHORIZATIONMANAGER_H_

#include <initializer_list>
#include <list>
#include <string>

#include "manager_exceptions.h"

#include "AppContext.h"
#include "AuthorizationHook.h"

class AuthorizationManager
{
    public:
        virtual ~AuthorizationManager(void) = default;

        virtual bool authorize(const std::string &hash,
                               std::initializer_list<std::string> roles) = 0;
        virtual bool authorize(const std::string &hash,
                               std::list<std::string> roles) = 0;
};

DEF_EX(CommonAuthorizationManagerException, ManagerException,
       "Common AuthorizationManager exception");
DEF_EX(NotAuthenticatedAuthorizationManagerException, CommonAuthorizationManagerException,
       "User isn't authenticated");
DEF_EX(EmptyListException, CommonAuthorizationManagerException,
       "Role list can't be empty");

#endif

