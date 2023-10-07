#ifndef _GROUPAGGREGATOR_HPP_
#define _GROUPAGGREGATOR_HPP_

#include "GroupAggregator.h"

#include <utility>

template <typename Class, typename GType, typename AType>
GroupAggregator<Class, GType, AType>::GroupAggregator(Getter getter, AggregatorCreator<Class, AType> &creator)
    : Base(getter), creator(creator)
{}

template <typename Class, typename GType, typename AType>
void GroupAggregator<Class, GType, AType>::apply(const Class &item)
{
    GType type = (item.*this->getter)();
    auto iter = this->res.find(type);

    if (this->res.end() != iter)
    {
        (*iter).second->apply(item);

        return;
    }

    this->res.emplace(std::make_pair(type, this->creator.create()));
    this->res[type]->apply(item);
}

template <typename Class, typename GType, typename AType>
const std::unordered_map<GType, std::shared_ptr<IQueryAggregatorResult<AType>>> &GroupAggregator<Class, GType, AType>::result(void)
{
    this->out.clear();

    for (auto item : this->res)
        this->out.emplace(item.first,
                          std::static_pointer_cast<IQueryAggregatorResult<AType>>(item.second));

    return this->out;
}

#endif

