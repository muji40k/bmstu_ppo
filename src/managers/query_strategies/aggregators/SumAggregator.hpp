#ifndef _SUMAGGREGATOR_HPP_
#define _SUMAGGREGATOR_HPP_

#include "SumAggregator.h"

template <typename Class, typename Type>
SumAggregator<Class, Type>::SumAggregator(Getter getter)
    : GetterAggregator<Class, Type>(getter)
{}

template <typename Class, typename Type>
void SumAggregator<Class, Type>::apply(const Class &item)
{
    this->res += (item.*this->getter)();
}

template <typename Class, typename Type>
const Type &SumAggregator<Class, Type>::result(void)
{
    return this->res;
}

#endif

