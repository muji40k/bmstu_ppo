#include "PlainQueryManager.h"

PlainQueryManager::PlainQueryManager(AppContext &context)
    : context(context)
{}

void PlainQueryManager::find(IQueryStrategy &strategy)
{
    strategy.execute(this->context);
}

