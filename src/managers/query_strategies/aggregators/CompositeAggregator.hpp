#ifndef _COMPOSITEAGGREGATOR_HPP_
#define _COMPOSITEAGGREGATOR_HPP_

#include "CompositeAggregator.h"

#include "typestring.h"

template <typename Class>
void CompositeAggregator<Class>::apply(const Class &item)
{
    for (auto pair : this->aggregators)
        for (auto iter : pair.second)
            iter->apply(item);
}

template <typename Class>
template <typename Type>
void CompositeAggregator<Class>::addAggregator(ResultQueryAggregator<Class, Type> &aggregator)
{
    const std::string &name = TypeName::get<Type>();
    auto iter = this->aggregators.find(name);

    if (this->aggregators.end() != iter)
    {
        (*iter).second.push_back(&aggregator);

        return;
    }

    this->aggregators.emplace(std::make_pair(name, std::list<IQueryAggregator<Class> *>({&aggregator})));
}

template <typename Class>
const typename CompositeAggregator<Class>::ResultType &CompositeAggregator<Class>::result(void)
{
    return this->aggregators;
}

template <typename Class>
template <typename Type>
std::list<IQueryAggregatorResult<Type> *> CompositeAggregator<Class>::cast(ResultIter &iter)
{
    const std::string &name = TypeName::get<Type>();

    if (name != (*iter).first)
        throw CALL_EX(BadCastCompositeAggregatorException);

    std::list<IQueryAggregatorResult<Type> *> out;

    for (auto agg : (*iter).second)
        out.push_back(dynamic_cast<IQueryAggregatorResult<Type> *>(agg));

    return out;
}

#endif

