#ifndef _ORDERAGGREGATOR_H_
#define _ORDERAGGREGATOR_H_

#include "GetterAggregator.h"

template <typename Class, typename Type>
class OrderAggregator : public GetterAggregator<Class, Type, Type>
{
    public:
        using Getter = typename GetterAggregator<Class, Type, Type>::Getter;
        using OrderFunc = bool (*)(const Type &, const Type &);

    public:
        OrderAggregator(Getter getter, OrderFunc func);
        virtual ~OrderAggregator(void) override = default;
        virtual void apply(const Class &item) override;
        virtual const Type &result(void) override;

    private:
        using Setter = void (OrderAggregator::*)(const Class &);

        void setFirst(const Class &item);
        void set(const Class &item);

        Setter setter = &OrderAggregator::setFirst;
        OrderFunc func = nullptr;
        Type res = Type();
};

DEF_EX(CommonOrderAggregatorException, CommonGetterAggregatorException,
       "Common AvgAggregator exception");
DEF_EX(NullptrOrderAggregatorException, CommonOrderAggregatorException,
       "OrderFunc can't be represented with nullptr");
DEF_EX(NoItemOrderAggregatorException, CommonOrderAggregatorException,
       "Set is empty");

#include "OrderAggregator.hpp"

#endif

