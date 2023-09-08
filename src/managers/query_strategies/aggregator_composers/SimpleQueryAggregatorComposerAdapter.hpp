#ifndef _SIMPLEQUERYAGGREGATORCOMPOSERADAPTER_HPP_
#define _SIMPLEQUERYAGGREGATORCOMPOSERADAPTER_HPP_

#include "SimpleQueryAggregatorComposerAdapter.h"

#include "typestring.h"

#include "ValueCriteria.h"
#include "CompositeCriteria.h"
#include "LogicCriteriaBuilder.h"

template <typename Class>
static std::shared_ptr<ICriteria> getIdItem(const unsigned long long id)
{
    return std::make_shared<ValueCriteria>(TypeName::getAttribute<Class>("id"),
                                           "=",
                                           std::to_string(id));
}

template <typename Class, typename RepoType>
SimpleQueryAggregatorComposerAdapter<Class, RepoType>::\
    SimpleQueryAggregatorComposerAdapter(Getter getter,
                                         const IQueryAggregator<Class> &aggregator)
    : getter(getter), aggregator(aggregator)
{
    if (nullptr == getter)
        throw CALL_EX(NullptrSimpleQueryAggregatorComposerAdapterException);
}

template <typename Class, typename RepoType>
const std::string &SimpleQueryAggregatorComposerAdapter<Class, RepoType>::type(void) const
{
    return TypeName::get<Class>();
}

template <typename Class, typename RepoType>
void SimpleQueryAggregatorComposerAdapter<Class, RepoType>::\
    run(AppContext &context, std::list<unsigned long long> ids,
        std::shared_ptr<const ICriteria> criteria)
try
{
    auto iter = ids.begin();
    LogicCriteriaBuilder builder (getIdItem<Class>(*iter));

    for (; ids.end() != iter; ++iter)
        builder.addOR(getIdItem<Class>(*iter));

    const ICriteria *target = builder.get().get();
    CompositeCriteria composite (*target, "and", *target);

    if (nullptr != criteria)
    {
        composite.criteria2 = *criteria;
        target = &composite;
    }

    SimpleQuery<Class, RepoType> query (this->getter, this->aggregator, *target);
    query.execute(context);
}
catch (AllocationLogicCriteriaBuilderException &)
{
    throw CALL_EX(AllocationSimpleQueryAggregatorComposerAdapterException);
}

#endif

