#include "DirectAggregate.h"

#include "ValueCriteria.h"

DirectAggregate::DirectAggregate(std::shared_ptr<QueryComposer> composer,
                                 std::list<std::shared_ptr<AggregatorComposer::AggregatorItem>> aggregators,
                                 const CriteriaBank &bank)
    : composer(composer), aggregators(aggregators), bank(bank)
{
    if (nullptr == composer)
        throw CALL_EX(NullptrDirectAggregateException);

    for (const std::shared_ptr<AggregatorComposer::AggregatorItem> &item : aggregators)
        if (nullptr == item)
            throw CALL_EX(NullptrDirectAggregateException);
}

void DirectAggregate::execute(AppContext &context)
{
    std::list<unsigned long long> ids = \
        this->composer->run(context, this->bank);

    static const AggregatorComposer acomposer;

    acomposer.run(context, this->bank, ids, this->aggregators);
}

