#include "ExecuteQueryCommand.h"

#include <memory>

#include "QueryManager.h"

ExecuteQueryCommand::ExecuteQueryCommand(IQueryStrategy &strategy)
    : strategy(strategy)
{}

void ExecuteQueryCommand::execute(AppContext &context)
try
{
    std::shared_ptr<QueryManager> manager = context.getQueryManager();
    manager->find(this->strategy);
}
catch (AllocationAppContextException &)
{
    throw CALL_EX(AllocationExecuteQueryCommandException);
}
catch (AllocationRepositoryContextException &)
{
    throw CALL_EX(AllocationExecuteQueryCommandException);
}
catch (CommonIQueryStrategyException &er)
{
    throw CALL_EX_MSG(StrategyExecuteQueryCommandException, er.what());
}
catch (CommonTimeChangeableRepositoryException &er)
{
    throw CALL_EX_MSG(RepositoryExecuteQueryCommandException, er.what());
}

