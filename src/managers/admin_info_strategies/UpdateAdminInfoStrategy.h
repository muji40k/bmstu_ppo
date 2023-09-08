#ifndef _UPDATEADMININFOSTRATEGY_H_
#define _UPDATEADMININFOSTRATEGY_H_

#include "AdminInfoManager.h"

class UpdateAdminInfoStrategy : public AdminInfoStrategy
{
    public:
        virtual ~UpdateAdminInfoStrategy(void) = default;
        virtual void apply(AppContext &context) = 0;
};

DEF_EX(UpdateAdminInfoStrategyException, CommonAdminInfoStrategyException,
       "Unable to update object");

#endif

