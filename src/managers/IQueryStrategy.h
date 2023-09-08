#ifndef _IQUERYSTRATEGY_H_
#define _IQUERYSTRATEGY_H_

#include "manager_exceptions.h"

#include "AppContext.h"

class IQueryStrategy
{
    public:
        virtual ~IQueryStrategy(void) = default;
        virtual void execute(AppContext &context) = 0;
};

DEF_EX(CommonIQueryStrategyException, ManagerException,
       "Common IQueryStrategy exception");

#endif

