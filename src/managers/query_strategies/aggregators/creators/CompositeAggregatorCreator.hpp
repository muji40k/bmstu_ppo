#ifndef _COMPOSITEAGGREGATORCREATOR_HPP_
#define _COMPOSITEAGGREGATORCREATOR_HPP_

#include "CompositeAggregatorCreator.h"

template <typename Class>
std::shared_ptr<ResultQueryAggregator<Class, typename CompositeAggregator<Class>::ResultType>> CompositeAggregatorCreator<Class>::create(void)
{
    return std::make_shared<CompositeAggregator<Class>>();
}

#endif

