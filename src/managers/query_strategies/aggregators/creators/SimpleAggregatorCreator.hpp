#ifndef _SIMPLEAGGREGATORCREATOR_HPP_
#define _SIMPLEAGGREGATORCREATOR_HPP_

#include "SimpleAggregatorCreator.h"

template <typename Class, typename Type>
SimpleAggregatorCreator<Class, Type>::SimpleAggregatorCreator(typename SimpleAggregator<Class, Type>::Getter getter)
    : getter(getter)
{}

template <typename Class, typename Type>
std::shared_ptr<ResultQueryAggregator<Class, std::list<Type>>> SimpleAggregatorCreator<Class, Type>::create(void)
{
    return std::make_shared<SimpleAggregator<Class, Type>>(this->getter);
}

#endif

