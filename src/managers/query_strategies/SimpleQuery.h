#ifndef _SIMPLEQUERY_H_
#define _SIMPLEQUERY_H_

#include <list>
#include <memory>

#include "ICriteria.h"

#include "IQueryAggregator.h"
#include "IQueryStrategy.h"

template <typename Class, typename RepoType>
class SimpleQuery : public IQueryStrategy
{
    public:
        using Getter = std::shared_ptr<RepoType> (RepositoryContext::*)(void);

    public:
        SimpleQuery(Getter getter, IQueryAggregator<Class> &aggregator);
        SimpleQuery(Getter getter, IQueryAggregator<Class> &aggregator,
                    const ICriteria &criteria);
        virtual ~SimpleQuery(void) override = default;

        virtual void execute(AppContext &context) override;

    private:
        Getter getter;
        IQueryAggregator<Class> &aggregator;
        const ICriteria *criteria = nullptr;
};

DEF_EX(NullptrSimpleQueryException, CommonIQueryStrategyException,
       "Getter can't be represented with nullptr");

#include "SimpleQuery.hpp"

#endif

