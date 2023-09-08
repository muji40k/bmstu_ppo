#ifndef _GROUPAGGREGATORCREATOR_HPP_
#define _GROUPAGGREGATORCREATOR_HPP_

#include "GroupAggregatorCreator.h"

template <typename Class, typename GType, typename AType>
GroupAggregatorCreator<Class, GType, AType>::GroupAggregatorCreator(typename GroupAggregator<Class, GType, AType>::Getter getter,
                                                                    AggregatorCreator<Class, AType> &creator)
    : getter(getter), creator(creator)
{}

template <typename Class, typename GType, typename AType>
std::shared_ptr<ResultQueryAggregator<Class, std::unordered_map<GType, std::shared_ptr<IQueryAggregatorResult<AType>>>>> GroupAggregatorCreator<Class, GType, AType>::create(void)
{
    return std::make_shared<GroupAggregator<Class, GType, AType>>(this->getter, this->creator);
}

#endif

