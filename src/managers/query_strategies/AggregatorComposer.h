#ifndef _AGGREGATORCOMPOSER_H_
#define _AGGREGATORCOMPOSER_H_

#include <memory>
#include <list>

#include "manager_exceptions.h"

#include "CriteriaBank.h"

#include "IQueryAggregator.h"
#include "AppContext.h"

class AggregatorComposer
{
    public:
        class AggregatorItem
        {
            public:
                virtual ~AggregatorItem(void) = default;
                virtual const std::string &type(void) const = 0;
                virtual void run(AppContext &context,
                                 std::list<unsigned long long> ids,
                                 std::shared_ptr<const ICriteria> criteria) = 0;
        };

    public:
        void run(AppContext &context, const CriteriaBank &bank,
                 std::list<unsigned long long> ids,
                 std::list<std::shared_ptr<AggregatorItem>> aggregators) const;
};

DEF_EX(CommonAggregatorComposerException, ManagerException,
       "Common AggregatorComposer exception");
DEF_EX(NullptrAggregatorComposerException, CommonAggregatorComposerException,
       "Can't add nullptr to aggregator items list");

#endif

