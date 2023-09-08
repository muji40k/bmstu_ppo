#ifndef _COUNTAGGREGATORCREATOR_HPP_
#define _COUNTAGGREGATORCREATOR_HPP_

#include "CountAggregatorCreator.h"

template <typename Class>
std::shared_ptr<ResultQueryAggregator<Class, size_t>> CountAggregatorCreator<Class>::create(void)
{
    return std::make_shared<CountAggregator<Class>>();
}

#endif

