#ifndef _SIMPLEAGGREGATORCREATOR_H_
#define _SIMPLEAGGREGATORCREATOR_H_

#include "AggregatorCreator.h"
#include "SimpleAggregator.h"

template <typename Class, typename Type>
class SimpleAggregatorCreator : public AggregatorCreator<Class, std::list<Type>>
{
    public:
        SimpleAggregatorCreator(typename SimpleAggregator<Class, Type>::Getter getter);
        virtual ~SimpleAggregatorCreator(void) override = default;
        virtual std::shared_ptr<ResultQueryAggregator<Class, std::list<Type>>> create(void) override;

    private:
        typename SimpleAggregator<Class, Type>::Getter getter;
};

#include "SimpleAggregatorCreator.hpp"

#endif

