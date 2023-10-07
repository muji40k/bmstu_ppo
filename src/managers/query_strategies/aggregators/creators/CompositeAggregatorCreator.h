#ifndef _COMPOSITEAGGREGATORCREATOR_H_
#define _COMPOSITEAGGREGATORCREATOR_H_

#include <list>
#include <initializer_list>

#include "AggregatorCreator.h"
#include "CompositeAggregator.h"

template <typename Class>
class CompositeAggregatorCreator : public AggregatorCreator<Class, typename CompositeAggregator<Class>::ResultType>
{
    public:
        virtual ~CompositeAggregatorCreator(void) override = default;
        virtual std::shared_ptr<ResultQueryAggregator<Class, typename CompositeAggregator<Class>::ResultType>> create(void) override;
};

#include "CompositeAggregatorCreator.hpp"

#endif

