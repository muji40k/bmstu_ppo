#ifndef _AVGAGGREGATORCREATOR_HPP_
#define _AVGAGGREGATORCREATOR_HPP_

#include "AvgAggregatorCreator.h"

template <typename Class, typename GType, typename RType>
AvgAggregatorCreator<Class, GType, RType>::AvgAggregatorCreator(typename AvgAggregator<Class, GType, RType>::Getter getter)
    : getter(getter)
{}

template <typename Class, typename GType, typename RType>
std::shared_ptr<ResultQueryAggregator<Class, RType>> AvgAggregatorCreator<Class, GType, RType>::create(void)
{
    return std::make_shared<AvgAggregator<Class, GType, RType>>(this->getter);
}

#endif

