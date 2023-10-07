#ifndef _COUNTAGGREGATOR_HPP_
#define _COUNTAGGREGATOR_HPP_

#include "CountAggregator.h"

template <typename Class>
void CountAggregator<Class>::apply(const Class &)
{
    this->amount++;
}

template <typename Class>
const size_t &CountAggregator<Class>::result(void)
{
    return this->amount;
}

#endif

