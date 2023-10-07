#ifndef _GETTERAGGREGATOR_HPP_
#define _GETTERAGGREGATOR_HPP_

#include "GetterAggregator.h"

template <typename Class, typename GType, typename RType>
GetterAggregator<Class, GType, RType>::GetterAggregator(Getter getter)
    : getter(getter)
{
    if (nullptr == getter)
        throw CALL_EX(NullptrGetterAggregatorException);
}

#endif

