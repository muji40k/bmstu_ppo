#ifndef _CREATEADMININFOSTRATEGY_H_
#define _CREATEADMININFOSTRATEGY_H_

#include "AdminInfoManager.h"

class CreateAdminInfoStrategy : public AdminInfoStrategy
{
    public:
        virtual ~CreateAdminInfoStrategy(void) = default;
        virtual void apply(AppContext &context) = 0;
};

DEF_EX(CreateAdminInfoStrategyException, CommonAdminInfoStrategyException,
       "Unable to create object");

#endif

