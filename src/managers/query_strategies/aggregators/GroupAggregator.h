#ifndef _GROUPAGGREGATOR_H_
#define _GROUPAGGREGATOR_H_

#include <memory>
#include <unordered_map>

#include "GetterAggregator.h"

#include "AggregatorCreator.h"

template <typename Class, typename GType, typename AType>
class GroupAggregator : public GetterAggregator<Class, GType,
                                                std::unordered_map<GType, std::shared_ptr<IQueryAggregatorResult<AType>>>>
{
    private:
        using Base   = GetterAggregator<Class, GType, std::unordered_map<GType, std::shared_ptr<IQueryAggregatorResult<AType>>>>;

    public:
        using Getter = typename GetterAggregator<Class, GType,
                                                 std::unordered_map<GType, std::shared_ptr<IQueryAggregatorResult<AType>>>>::Getter;

    public:
        GroupAggregator(Getter getter, AggregatorCreator<Class, AType> &creator);
        virtual ~GroupAggregator(void) override = default;
        virtual void apply(const Class &item) override;
        virtual const std::unordered_map<GType, std::shared_ptr<IQueryAggregatorResult<AType>>> &result(void) override;

    private:
        AggregatorCreator<Class, AType> &creator;
        std::unordered_map<GType, std::shared_ptr<ResultQueryAggregator<Class, AType>>> res;
        std::unordered_map<GType, std::shared_ptr<IQueryAggregatorResult<AType>>> out;
};

#include "GroupAggregator.hpp"

#endif

