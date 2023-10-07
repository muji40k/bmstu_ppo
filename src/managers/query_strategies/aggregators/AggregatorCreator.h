#ifndef _AGGREGATORCREATOR_H_
#define _AGGREGATORCREATOR_H_

#include <memory>

#include "IQueryAggregator.h"

template <typename Class, typename T>
class AggregatorCreator
{
    public:
        virtual ~AggregatorCreator(void) = default;
        virtual std::shared_ptr<ResultQueryAggregator<Class, T>> create(void) = 0;
};

#endif

