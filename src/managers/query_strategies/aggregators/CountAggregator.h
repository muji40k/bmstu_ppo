#ifndef _COUNTAGGREGATOR_H_
#define _COUNTAGGREGATOR_H_

#include "IQueryAggregator.h"

template <typename Class>
class CountAggregator : public ResultQueryAggregator<Class, size_t>
{
    public:
        virtual ~CountAggregator(void) override = default;
        virtual void apply(const Class &item) override;
        virtual const size_t &result(void) override;

    private:
        size_t amount = 0;
};

#include "CountAggregator.hpp"

#endif

