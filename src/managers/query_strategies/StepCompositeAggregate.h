#ifndef _STEPCOMPOSITEAGGREGATE_H_
#define _STEPCOMPOSITEAGGREGATE_H_

#include <memory>
#include <list>

#include "IQueryStrategy.h"

#include "AppContext.h"
#include "CriteriaBank.h"

#include "QueryComposer.h"
#include "AggregatorComposer.h"

class StepCompositeAggregate : public IQueryStrategy
{
    public:
        class Linker
        {
            public:
                virtual ~Linker(void) = default;
                virtual void link(CriteriaBank &bank, std::list<unsigned long long> ids) = 0;
        };

    public:
        StepCompositeAggregate(std::list<std::shared_ptr<QueryComposer>> composers,
                               std::list<std::shared_ptr<Linker>> linkers,
                               std::list<std::shared_ptr<AggregatorComposer::AggregatorItem>> aggregators,
                               const CriteriaBank &bank);
        virtual ~StepCompositeAggregate(void) override = default;

        virtual void execute(AppContext &context) override;

    private:
        std::list<std::shared_ptr<QueryComposer>> composers;
        std::list<std::shared_ptr<Linker>> linkers;
        std::list<std::shared_ptr<AggregatorComposer::AggregatorItem>> aggregators;
        const CriteriaBank &bank;
};

DEF_EX(CommonStepCompositeAggregateException, CommonIQueryStrategyException,
       "Common StepCompositeAggregate exception");
DEF_EX(NullptrStepCompositeAggregateException, CommonStepCompositeAggregateException,
       "Nullptr occured");
DEF_EX(IncompatibleStepCompositeAggregateException, CommonStepCompositeAggregateException,
       "Sizes of composer's and linker's lists are incompatible");

DEF_EX(CommonStepCompositeAggregateLinkerException, CommonStepCompositeAggregateException,
       "Common StepCompositeAggregateLink exception");

#endif

