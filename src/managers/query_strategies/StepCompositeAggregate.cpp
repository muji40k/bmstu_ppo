#include "StepCompositeAggregate.h"

StepCompositeAggregate::StepCompositeAggregate(std::list<std::shared_ptr<QueryComposer>> composers,
                                               std::list<std::shared_ptr<Linker>> linkers,
                                               std::list<std::shared_ptr<AggregatorComposer::AggregatorItem>> aggregators,
                                               const CriteriaBank &bank)
    : composers(composers), linkers(linkers), aggregators(aggregators),
      bank(bank)
{
    if (composers.size() != linkers.size() + 1)
        throw CALL_EX(IncompatibleStepCompositeAggregateException);

    for (auto item : composers)
        if (nullptr == item)
            throw CALL_EX(NullptrStepCompositeAggregateException);

    for (auto item : linkers)
        if (nullptr == item)
            throw CALL_EX(NullptrStepCompositeAggregateException);

    for (auto item : aggregators)
        if (nullptr == item)
            throw CALL_EX(NullptrStepCompositeAggregateException);
}

void StepCompositeAggregate::execute(AppContext &context)
{
    CriteriaBank copy = this->bank;

    auto citer = this->composers.begin();
    auto liter = this->linkers.begin();
    std::list<unsigned long long> ids = (*citer)->run(context, copy);

    for (; this->composers.end() != citer; ++citer, ++liter)
    {
        (*liter)->link(copy, ids);
        ids = (*citer)->run(context, copy);
    }

    static const AggregatorComposer acomposer;

    acomposer.run(context, copy, ids, this->aggregators);
}

