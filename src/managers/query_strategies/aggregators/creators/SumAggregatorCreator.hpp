#ifndef _SUMAGGREGATORCREATOR_HPP_
#define _SUMAGGREGATORCREATOR_HPP_

#include "SumAggregatorCreator.h"

template <typename Class, typename Type>
SumAggregatorCreator<Class, Type>::SumAggregatorCreator(typename SumAggregator<Class, Type>::Getter getter)
    : getter(getter)
{}

template <typename Class, typename Type>
std::shared_ptr<ResultQueryAggregator<Class, Type>> SumAggregatorCreator<Class, Type>::create(void)
{
    return std::make_shared<SumAggregator<Class, std::list<Type>>>(this->getter);
}

#endif

