#include "QueryManager.h"

QueryManager::QueryManager(AppContext &context)
    : context(context)
{}

void QueryManager::find(IQueryStrategy &strategy)
{
    strategy.execute(this->context);
}

