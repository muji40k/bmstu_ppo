#ifndef _ADMININFOMANAGER_H_
#define _ADMININFOMANAGER_H_

#include "manager_exceptions.h"

#include "AppContext.h"

class AdminInfoStrategy
{
    public:
        virtual ~AdminInfoStrategy(void) = default;
        virtual void apply(AppContext &context) = 0;
};

class AdminInfoManager
{
    public:
        virtual ~AdminInfoManager(void) = default;

        virtual void process(std::string hash, AdminInfoStrategy &strategy) = 0;
};

DEF_EX(CommonAdminInfoStrategyException, ManagerException,
       "Common AdminInfoStrategy exception");

DEF_EX(CommonAdminInfoManagerException, ManagerException,
       "Common AdminInfoManager exception");
DEF_EX(NotAuthenticatedAdminInfoManagerException, CommonAdminInfoManagerException,
       "Hash doesn't specify any user");
DEF_EX(NotAuthorizedAdminInfoManagerException, CommonAdminInfoManagerException,
       "User isn't an admin");

#endif

