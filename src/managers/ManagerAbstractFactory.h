#ifndef _MANAGERABSTRACTFACTORY_H_
#define _MANAGERABSTRACTFACTORY_H_

#include <memory>

#include "manager_exceptions.h"

class LoginManager;
class AuthorizationManager;
class UserInfoManager;
class AdminInfoManager;
class UserRequestManager;
class AdminRequestManager;
class QueryManager;

class ManagerAbstractFactory
{
    public:
        virtual ~ManagerAbstractFactory(void) = default;

#define ADD_REPO(type) \
        virtual std::shared_ptr<type> make##type(void) = 0

        ADD_REPO(LoginManager);
        ADD_REPO(AuthorizationManager);
        ADD_REPO(UserInfoManager);
        ADD_REPO(AdminInfoManager);
        ADD_REPO(UserRequestManager);
        ADD_REPO(AdminRequestManager);
        ADD_REPO(QueryManager);

#undef ADD_REPO
};

DEF_EX(CommonManagerAbstractFactoryException, ManagerException,
       "Common RepositoManagerFactory exception");
DEF_EX(AllocationManagerAbstractFactoryException,
       CommonManagerAbstractFactoryException,
       "RepositoManagerFactory allocation error occured");

#endif

