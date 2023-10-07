#include "CompositeQuery.h"

void CompositeQuery::execute(AppContext &context)
{
    for (auto item : this->queries)
        item->execute(context);
}

void CompositeQuery::addQuery(IQueryStrategy &query)
{
    this->queries.push_back(&query);
}

