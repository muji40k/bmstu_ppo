#ifndef _SIMPLEAGGREGATOR_H_
#define _SIMPLEAGGREGATOR_H_

#include <list>

#include "GetterAggregator.h"

template <typename Class, typename Type>
class SimpleAggregator : public GetterAggregator<Class, Type, std::list<Type>>
{
    public:
        using Getter = typename GetterAggregator<Class, Type, std::list<Type>>::Getter;

    public:
        SimpleAggregator(Getter getter);
        virtual ~SimpleAggregator(void) override = default;
        virtual void apply(const Class &item) override;
        virtual const std::list<Type> &result(void) override;

    private:
        std::list<Type> res;
};

#include "SimpleAggregator.hpp"

#endif

