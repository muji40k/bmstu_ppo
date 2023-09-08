#ifndef _GENERICLINKER_H_
#define _GENERICLINKER_H_

#include "StepCompositeAggregate.h"

#include "LogicCriteriaBuilder.h"

class GenericLinker : public StepCompositeAggregate::Linker
{
    public:
        using LinkFunction = std::shared_ptr<const ICriteria> (*)(const unsigned long long);

    public:
        GenericLinker(LinkFunction func, const std::string &name);
        virtual ~GenericLinker(void) override = default;
        virtual void link(CriteriaBank &bank, std::list<unsigned long long> ids) override;

    private:
        LinkFunction func;
        const std::string &name;
        std::list<LogicCriteriaBuilder> builders;
};

DEF_EX(CommonGenericLinkerException, CommonStepCompositeAggregateLinkerException,
       "Common GenericLinker exception");
DEF_EX(AllocationGenericLinkerException, CommonGenericLinkerException,
       "Unable to allocate criteria");
DEF_EX(NullptrGenericLinkerException, CommonGenericLinkerException,
       "LinkFunction can't be represented with nullptr");

#endif

