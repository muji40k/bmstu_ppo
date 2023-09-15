#ifndef _EXECUTEQUERYCOMMAND_H_
#define _EXECUTEQUERYCOMMAND_H_

#include "QueryCommand.h"
#include "IQueryStrategy.h"

class ExecuteQueryCommand : public QueryCommand
{
    public:
        ExecuteQueryCommand(IQueryStrategy &strategy);
        virtual ~ExecuteQueryCommand(void) override = default;
        virtual void execute(AppContext &context) override;

    private:
        IQueryStrategy &strategy;
};

DEF_EX(CommonExecuteQueryCommandException, CommonQueryCommandException,
       "Common ExecuteQueryCommand exception");
DEF_EX(AllocationExecuteQueryCommandException, CommonExecuteQueryCommandException,
       "Unable to allocate ExecuteQueryManager");
DEF_EX(StrategyExecuteQueryCommandException, CommonExecuteQueryCommandException, "");
DEF_EX(RepositoryExecuteQueryCommandException, CommonExecuteQueryCommandException, "");

#endif

