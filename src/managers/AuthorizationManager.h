#ifndef _AUTHORIZATIONMANAGER_H_
#define _AUTHORIZATIONMANAGER_H_

#include <initializer_list>
#include <list>
#include <string>

#include "manager_exceptions.h"

#include "AppContext.h"
#include "User.h"
#include "AuthorizationHook.h"

class AuthorizationManager
{
    public:
        AuthorizationManager(AppContext &context,
                             std::shared_ptr<AuthorizationHook> hook = nullptr);
        virtual ~AuthorizationManager(void) = default;

        virtual bool authorize(const std::string &hash,
                               std::initializer_list<std::string> roles);
        virtual bool authorize(const std::string &hash,
                               std::list<std::string> roles);

    private:
        template <typename Container>
        bool innerAuthorize(const std::string &hash,
                            const Container &container);

        AppContext &context;
        std::shared_ptr<AuthorizationHook> hook = nullptr;
};

DEF_EX(CommonAuthorizationManagerException, ManagerException,
       "Common AuthorizationManager exception");
DEF_EX(NotAuthenticatedAuthorizationManagerException, CommonAuthorizationManagerException,
       "User isn't authenticated");
DEF_EX(EmptyListException, CommonAuthorizationManagerException,
       "Role list can't be empty");

#endif

