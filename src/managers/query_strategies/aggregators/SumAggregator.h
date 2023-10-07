#ifndef _SUMAGGREGATOR_H_
#define _SUMAGGREGATOR_H_

#include "GetterAggregator.h"

template <typename Class, typename Type>
class SumAggregator : public GetterAggregator<Class, Type, Type>
{
    public:
        using Getter = typename GetterAggregator<Class, Type, Type>::Getter;

    public:
        SumAggregator(Getter getter);
        virtual ~SumAggregator(void) override = default;
        virtual void apply(const Class &item) override;
        virtual const Type &result(void) override;

    private:
        Type res = Type();
};

#include "SumAggregator.hpp"

#endif

