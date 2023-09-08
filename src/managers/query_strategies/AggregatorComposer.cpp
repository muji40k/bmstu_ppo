#include "AggregatorComposer.h"

void AggregatorComposer::run(AppContext &context, const CriteriaBank &bank,
                             std::list<unsigned long long> ids,
                             std::list<std::shared_ptr<AggregatorItem>> aggregators) const
{
    if (ids.empty())
        return;

    for (std::shared_ptr<AggregatorItem> item : aggregators)
    {
        if (nullptr == item)
            throw CALL_EX(NullptrAggregatorComposerException);

        try
        {
            std::shared_ptr<const ICriteria> criteria = bank.get(item->type());
            item->run(context, ids, criteria);
        }
        catch (NotSetCriteriaBankException &)
        {}
    }
}

