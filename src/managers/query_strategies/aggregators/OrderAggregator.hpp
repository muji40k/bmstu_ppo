#ifndef _ORDERAGGREGATOR_HPP_
#define _ORDERAGGREGATOR_HPP_

#include "OrderAggregator.h"

template <typename Class, typename Type>
OrderAggregator<Class, Type>::OrderAggregator(Getter getter, OrderFunc func)
    : GetterAggregator<Class, Type>(getter), func(func)
{
    if (nullptr == func)
        throw CALL_EX(NullptrOrderAggregatorException);
}

template <typename Class, typename Type>
void OrderAggregator<Class, Type>::apply(const Class &item)
{
    (this->*(this->setter))(item);
}

template <typename Class, typename Type>
const Type &OrderAggregator<Class, Type>::result(void)
{
    if (&OrderAggregator<Class, Type>::setFirst == this->setter)
        throw CALL_EX(NoItemOrderAggregatorException);

    return this->res;
}

template <typename Class, typename Type>
void OrderAggregator<Class, Type>::setFirst(const Class &item)
{
    this->res = (item.*this->getter)();
    this->setter = &OrderAggregator<Class, Type>::set;
}

template <typename Class, typename Type>
void OrderAggregator<Class, Type>::set(const Class &item)
{
    const Type &val = (item.*this->getter)();

    if (this->func(val, this->res))
        this->res = val;
}

#endif

