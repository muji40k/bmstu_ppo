#ifndef _GETADMININFOSTRATEGY_H_
#define _GETADMININFOSTRATEGY_H_

#include "AdminInfoManager.h"

template <typename Type>
class GetStrategyResult
{
    public:
        virtual ~GetStrategyResult(void) = default;
        virtual Type result(void) = 0;
};

class GetAdminInfoStrategy : public AdminInfoStrategy
{
    public:
        virtual ~GetAdminInfoStrategy(void) = default;
        virtual void apply(AppContext &context) = 0;
};

DEF_EX(GetAdminInfoStrategyException, CommonAdminInfoStrategyException,
       "Unable to get object");

#endif

