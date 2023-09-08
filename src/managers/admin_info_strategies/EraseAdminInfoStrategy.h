#ifndef _ERASEADMININFOSTRATEGY_H_
#define _ERASEADMININFOSTRATEGY_H_

#include "AdminInfoManager.h"

class EraseAdminInfoStrategy : public AdminInfoStrategy
{
    public:
        virtual ~EraseAdminInfoStrategy(void) = default;
        virtual void apply(AppContext &context) = 0;
};

DEF_EX(EraseAdminInfoStrategyException, CommonAdminInfoStrategyException,
       "Unable to erase object");

#endif

