#ifndef _GETTERAGGREGATOR_H_
#define _GETTERAGGREGATOR_H_

#include <list>

#include "IQueryAggregator.h"

template <typename Class, typename GType, typename RType = GType>
class GetterAggregator : public ResultQueryAggregator<Class, RType>
{
    public:
        using Getter = const GType &(Class::*)(void) const;

    public:
        GetterAggregator(Getter getter);
        virtual ~GetterAggregator(void) override = default;

    protected:
        Getter getter;
};

DEF_EX(CommonGetterAggregatorException, CommonIQueryAggregatorException,
       "Common GetterAggregator exception");
DEF_EX(NullptrGetterAggregatorException, CommonGetterAggregatorException,
       "Getter can't be represented with nullptr");

#include "GetterAggregator.hpp"

#endif

