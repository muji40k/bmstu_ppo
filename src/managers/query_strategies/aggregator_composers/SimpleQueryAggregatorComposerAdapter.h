#ifndef _SIMPLEQUERYAGGREGATORCOMPOSERADAPTER_H_
#define _SIMPLEQUERYAGGREGATORCOMPOSERADAPTER_H_

#include "manager_exceptions.h"

#include "AggregatorComposer.h"
#include "SimpleQuery.h"
#include "IQueryAggregator.h"

template <typename Class, typename RepoType>
class SimpleQueryAggregatorComposerAdapter : public AggregatorComposer::AggregatorItem
{
    public:
        using Getter = typename SimpleQuery<Class, RepoType>::Getter;

    public:
        SimpleQueryAggregatorComposerAdapter(Getter getter,
                                             const IQueryAggregator<Class> &aggregator);
        virtual ~SimpleQueryAggregatorComposerAdapter(void) override = default;
        virtual const std::string &type(void) const override;
        virtual void run(AppContext &context,
                         std::list<unsigned long long> ids,
                         std::shared_ptr<const ICriteria> criteria) override;

    private:
        Getter getter;
        const IQueryAggregator<Class> &aggregator;
};

DEF_EX(CommonSimpleQueryAggregatorComposerAdapterException, CommonAggregatorComposerException,
       "Common QueryAggregatorComposer exception");
DEF_EX(NullptrSimpleQueryAggregatorComposerAdapterException, CommonSimpleQueryAggregatorComposerAdapterException,
       "Getter isn't set");
DEF_EX(AllocationSimpleQueryAggregatorComposerAdapterException, CommonSimpleQueryAggregatorComposerAdapterException,
       "Unable to allocate query");

#include "SimpleQueryAggregatorComposerAdapter.hpp"

#endif

