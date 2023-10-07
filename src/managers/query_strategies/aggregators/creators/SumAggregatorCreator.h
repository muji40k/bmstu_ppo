#ifndef _SUMAGGREGATORCREATOR_H_
#define _SUMAGGREGATORCREATOR_H_

#include "AggregatorCreator.h"
#include "SumAggregator.h"

template <typename Class, typename Type>
class SumAggregatorCreator : public AggregatorCreator<Class, Type>
{
    public:
        SumAggregatorCreator(typename SumAggregator<Class, Type>::Getter getter);
        virtual ~SumAggregatorCreator(void) override = default;
        virtual std::shared_ptr<ResultQueryAggregator<Class, Type>> create(void) override;

    private:
        typename SumAggregator<Class, Type>::Getter getter;
};

#include "SumAggregatorCreator.hpp"

#endif

