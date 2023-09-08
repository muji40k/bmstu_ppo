#ifndef _QUERYMANAGER_H_
#define _QUERYMANAGER_H_

#include "AppContext.h"
#include "IQueryStrategy.h"

class QueryManager
{
    public:
        QueryManager(AppContext &context);
        virtual ~QueryManager(void) = default;

        virtual void find(IQueryStrategy &strategy);

    private:
        AppContext &context;
};

#endif

