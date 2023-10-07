#ifndef _PLAINQUERYMANAGER_H_
#define _PLAINQUERYMANAGER_H_

#include "QueryManager.h"

class PlainQueryManager : public QueryManager
{
    public:
        PlainQueryManager(AppContext &context);
        virtual ~PlainQueryManager(void) override = default;

        virtual void find(IQueryStrategy &strategy) override;

    private:
        AppContext &context;
};

#endif

