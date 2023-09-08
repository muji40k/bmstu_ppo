#ifndef _GROUPAGGREGATORCREATOR_H_
#define _GROUPAGGREGATORCREATOR_H_

#include "AggregatorCreator.h"
#include "GroupAggregator.h"

template <typename Class, typename GType, typename AType>
class GroupAggregatorCreator : public AggregatorCreator<Class, std::unordered_map<GType, std::shared_ptr<IQueryAggregatorResult<AType>>>>
{
    public:
        GroupAggregatorCreator(typename GroupAggregator<Class, GType, AType>::Getter getter,
                               AggregatorCreator<Class, AType> &creator);
        virtual ~GroupAggregatorCreator(void) override = default;
        virtual std::shared_ptr<ResultQueryAggregator<Class, std::unordered_map<GType, std::shared_ptr<IQueryAggregatorResult<AType>>>>> create(void) override;

    private:
        typename GroupAggregator<Class, GType, AType>::Getter getter;
        AggregatorCreator<Class, AType> &creator;
};

#endif

