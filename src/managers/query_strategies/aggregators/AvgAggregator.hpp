#ifndef _AVGAGGREGATOR_HPP_
#define _AVGAGGREGATOR_HPP_

#include "AvgAggregator.h"

template <typename Class, typename GType, typename RType>
AvgAggregator<Class, GType, RType>::AvgAggregator(Getter getter)
    : GetterAggregator<Class, GType>(getter)
{}

template <typename Class, typename GType, typename RType>
void AvgAggregator<Class, GType, RType>::apply(const Class &item)
{
    this->sum += (item.*this->getter)();
    this->amount++;
}

template <typename Class, typename GType, typename RType>
const RType &AvgAggregator<Class, GType, RType>::result(void)
{
    if (0 == this->amount)
        throw CALL_EX(NoItemAvgAggregatorException);

    return this->res = this->sum / this->amount;
}

#endif

