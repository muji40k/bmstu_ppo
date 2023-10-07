#ifndef _AVGAGGREGATORCREATOR_H_
#define _AVGAGGREGATORCREATOR_H_

#include "AggregatorCreator.h"
#include "AvgAggregator.h"

template <typename Class, typename GType, typename RType = GType>
class AvgAggregatorCreator : public AggregatorCreator<Class, RType>
{
    public:
        AvgAggregatorCreator(typename AvgAggregator<Class, GType, RType>::Getter getter);
        virtual ~AvgAggregatorCreator(void) override = default;
        virtual std::shared_ptr<ResultQueryAggregator<Class, RType>> create(void) override;

    private:
        typename AvgAggregator<Class, GType, RType>::Getter getter;
};

#include "AvgAggregatorCreator.hpp"

#endif

