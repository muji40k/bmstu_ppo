#ifndef _DIRECTAGGREGATE_H_
#define _DIRECTAGGREGATE_H_

#include <memory>

#include "IQueryStrategy.h"

#include "AppContext.h"
#include "CriteriaBank.h"

#include "QueryComposer.h"
#include "AggregatorComposer.h"

class DirectAggregate : public IQueryStrategy
{
    public:
        DirectAggregate(std::shared_ptr<QueryComposer> composer,
                        std::list<std::shared_ptr<AggregatorComposer::AggregatorItem>> aggregators,
                        const CriteriaBank &bank);
        virtual ~DirectAggregate(void) override = default;

        virtual void execute(AppContext &context) override;

    private:
        std::shared_ptr<QueryComposer> composer;
        std::list<std::shared_ptr<AggregatorComposer::AggregatorItem>> aggregators;
        const CriteriaBank &bank;

};

DEF_EX(CommonDirectAggregateException, CommonIQueryStrategyException,
       "Common DirectAggregate exception");
DEF_EX(NullptrDirectAggregateException, CommonDirectAggregateException,
       "Nullptr occured");

#endif

