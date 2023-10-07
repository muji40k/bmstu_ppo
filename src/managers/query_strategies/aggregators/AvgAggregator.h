#ifndef _AVGAGGREGATOR_H_
#define _AVGAGGREGATOR_H_

#include "GetterAggregator.h"

template <typename Class, typename GType, typename RType = GType>
class AvgAggregator : public GetterAggregator<Class, GType, RType>
{
    public:
        using Getter = typename GetterAggregator<Class, GType, RType>::Getter;

    public:
        AvgAggregator(Getter getter);
        virtual ~AvgAggregator(void) override = default;
        virtual void apply(const Class &item) override;
        virtual const RType &result(void) override;

    private:
        RType res;
        RType sum = RType();
        size_t amount = 0;
};

DEF_EX(CommonAvgAggregatorException, CommonGetterAggregatorException,
       "Common AvgAggregator exception");
DEF_EX(NoItemAvgAggregatorException, CommonAvgAggregatorException,
       "Set is empty");

#include "AvgAggregator.hpp"

#endif

