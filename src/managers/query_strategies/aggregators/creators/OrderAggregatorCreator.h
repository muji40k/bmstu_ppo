#ifndef _ORDERAGGREGATORCREATOR_H_
#define _ORDERAGGREGATORCREATOR_H_

#include "AggregatorCreator.h"
#include "OrderAggregator.h"

template <typename Class, typename Type>
class OrderAggregatorCreator : public AggregatorCreator<Class, Type>
{
    public:
        OrderAggregatorCreator(typename OrderAggregator<Class, Type>::Getter getter,
                               typename OrderAggregator<Class, Type>::OrderFunc func);
        virtual ~OrderAggregatorCreator(void) override = default;
        virtual std::shared_ptr<ResultQueryAggregator<Class, Type>> create(void) override;

    private:
        typename OrderAggregator<Class, Type>::Getter getter;
        typename OrderAggregator<Class, Type>::OrderFunc func;
};

#include "OrderAggregatorCreator.hpp"

#endif

