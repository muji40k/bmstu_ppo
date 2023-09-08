#ifndef _AUTHORIZATIONMANAGER_H_
#define _AUTHORIZATIONMANAGER_H_

#include <initializer_list>
#include <list>
#include <string>

#include "manager_exceptions.h"

#include "RepositoryContext.h"
#include "User.h"

class AuthorizationManager
{
    public:
        AuthorizationManager(RepositoryContext &context);
        virtual ~AuthorizationManager(void) = default;

        virtual bool authorize(const User &user,
                               std::initializer_list<std::string> roles);
        virtual bool authorize(const User &user, std::list<std::string> roles);

    private:
        template <typename Container>
        bool innerAuthorize(const User &user, const Container &container);

        RepositoryContext &context;
};

DEF_EX(CommonAuthorizationManagerException, ManagerException,
       "Common AuthorizationManager exception");
DEF_EX(EmptyListException, CommonAuthorizationManagerException,
       "Role list can't be empty");

#endif

