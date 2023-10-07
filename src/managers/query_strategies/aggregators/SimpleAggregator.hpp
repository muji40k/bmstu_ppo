#ifndef _SIMPLEAGGREGATOR_HPP_
#define _SIMPLEAGGREGATOR_HPP_

#include "SimpleAggregator.h"

template <typename Class, typename Type>
SimpleAggregator<Class, Type>::SimpleAggregator(Getter getter)
    : GetterAggregator<Class, Type, std::list<Type>>(getter)
{}

template <typename Class, typename Type>
void SimpleAggregator<Class, Type>::apply(const Class &item)
{
    this->res.push_back((item.*this->getter)());
}

template <typename Class, typename Type>
const std::list<Type> &SimpleAggregator<Class, Type>::result(void)
{
    return this->res;
}

#endif

