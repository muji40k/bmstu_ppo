#ifndef _QUERYMANAGER_H_
#define _QUERYMANAGER_H_

#include "AppContext.h"
#include "IQueryStrategy.h"

#include "manager_exceptions.h"

class QueryManager
{
    public:
        virtual ~QueryManager(void) = default;

        virtual void find(IQueryStrategy &strategy) = 0;
};

DEF_EX(CommonQueryManagerException, ManagerException,
       "Common QueryCommand exception");

#endif

