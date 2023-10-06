#ifndef _LOGQUERYMANAGER_H_
#define _LOGQUERYMANAGER_H_

#include <memory>

#include "ILogger.h"
#include "QueryManager.h"

class LogQueryManager : public QueryManager
{
    public:
        LogQueryManager(std::shared_ptr<ILogger> logger,
                        std::shared_ptr<QueryManager> manager);
        virtual ~LogQueryManager(void) override = default;

        virtual void find(IQueryStrategy &strategy) override;

    private:
        std::shared_ptr<ILogger> logger;
        std::shared_ptr<QueryManager> manager;
};

DEF_EX(CommonLogQueryManagerException, CommonQueryManagerException,
       "Common LogQueryManager exception");
DEF_EX(NullptrLogQueryManagerException, CommonLogQueryManagerException,
       "Nullptr occured");

#endif

