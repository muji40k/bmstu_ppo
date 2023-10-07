#ifndef _ORDERAGGREGATORCREATOR_HPP_
#define _ORDERAGGREGATORCREATOR_HPP_

#include "OrderAggregatorCreator.h"

template <typename Class, typename Type>
OrderAggregatorCreator<Class, Type>::OrderAggregatorCreator(typename OrderAggregator<Class, Type>::Getter getter,
                                                            typename OrderAggregator<Class, Type>::OrderFunc func)
    : getter(getter), func(func)
{}

template <typename Class, typename Type>
std::shared_ptr<ResultQueryAggregator<Class, Type>> OrderAggregatorCreator<Class, Type>::create(void)
{
    return std::make_shared<OrderAggregator<Class, Type>>(this->getter, this->func);
}

#endif

