#ifndef _COMPOSITEAGGREGATOR_H_
#define _COMPOSITEAGGREGATOR_H_

#include <list>
#include <unordered_map>

#include "IQueryAggregator.h"

template <typename Class>
class CompositeAggregator : public ResultQueryAggregator<Class,
    std::unordered_map<std::string, std::list<IQueryAggregator<Class> *>>>
{
    public:
        using ResultType = std::unordered_map<std::string, std::list<IQueryAggregator<Class> *>>;
        using ResultIter = typename ResultType::const_iterator;

    public:
        virtual ~CompositeAggregator(void) override = default;
        virtual void apply(const Class &item) override;
        virtual const ResultType &result(void) override;

        template <typename Type>
        void addAggregator(ResultQueryAggregator<Class, Type> &aggregator);

        template <typename Type>
        static std::list<IQueryAggregatorResult<Type> *> cast(ResultIter &iter);

    private:
        ResultType aggregators;
};

DEF_EX(CommonCompositeAggregatorException, CommonIQueryAggregatorException,
       "Common CompositeAggregator exception");
DEF_EX(BadCastCompositeAggregatorException, CommonCompositeAggregatorException,
       "Unable to cast iterator");

#include "CompositeAggregator.hpp"

#endif

