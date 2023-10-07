#ifndef _SIMPLEQUERY_HPP_
#define _SIMPLEQUERY_HPP_

#include "SimpleQuery.h"

template <typename Class, typename RepoType>
SimpleQuery<Class, RepoType>::SimpleQuery(Getter getter, IQueryAggregator<Class> &aggregator)
    : getter(getter), aggregator(aggregator)
{
    if (nullptr == getter)
        throw CALL_EX(NullptrSimpleQueryException);
}

template <typename Class, typename RepoType>
SimpleQuery<Class, RepoType>::SimpleQuery(Getter getter, IQueryAggregator<Class> &aggregator,
                                          const ICriteria &criteria)
    : SimpleQuery(getter, aggregator)
{
    this->criteria = &criteria;
}

template <typename Class, typename RepoType>
void SimpleQuery<Class, RepoType>::execute(AppContext &context)
{
    auto repo = ((context.getRepositoryContext()).*this->getter)();
    std::shared_ptr<ITimeChangeableRepositorySet<Class>> set = nullptr;

    if (nullptr == this->criteria)
        set = repo->getAll();
    else
        set = repo->get(*this->criteria);

    for (auto id_iter = set->begin(),
              id_end = set->end();
         id_end->notEqual(id_iter);
         id_iter->next())
        this->aggregator.apply(set->beginId(id_iter)->get());
}

#endif

