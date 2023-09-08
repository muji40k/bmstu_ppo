#ifndef _COUNTAGGREGATORCREATOR_H_
#define _COUNTAGGREGATORCREATOR_H_

#include "AggregatorCreator.h"
#include "CountAggregator.h"

template <typename Class>
class CountAggregatorCreator : public AggregatorCreator<Class, size_t>
{
    public:
        virtual ~CountAggregatorCreator(void) override = default;
        virtual std::shared_ptr<ResultQueryAggregator<Class, size_t>> create(void) override;
};

#include "CountAggregatorCreator.hpp"

#endif

