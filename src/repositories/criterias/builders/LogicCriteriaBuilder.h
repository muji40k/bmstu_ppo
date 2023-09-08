#ifndef _LOGICCRITERIABUILDER_H_
#define _LOGICCRITERIABUILDER_H_

#include <list>

#include "repository_exceptions.h"

#include "CompositeCriteria.h"

#include "ICriteriaBuilder.h"

class LogicCriteriaBuilder : public ICriteriaBuilder
{
    public:
        LogicCriteriaBuilder(std::shared_ptr<const ICriteria> start, bool inv=false);
        virtual ~LogicCriteriaBuilder(void) override = default;
        virtual std::shared_ptr<const ICriteria> get(void) const override;

        void addAND(std::shared_ptr<const ICriteria> criteria, bool inv=false);
        void addOR(std::shared_ptr<const ICriteria> criteria, bool inv=false);

    private:
        std::shared_ptr<const ICriteria> addCurrent(std::shared_ptr<const ICriteria> criteria, bool inv);
        void add(std::string op, std::shared_ptr<const ICriteria> current, bool inv);

    private:
        std::list<std::shared_ptr<const ICriteria>> main_bank;
        std::list<std::shared_ptr<const ICriteria>> not_bank;
        std::list<std::shared_ptr<CompositeCriteria>> composite_bank;
        std::shared_ptr<const ICriteria> target;
};

DEF_EX(CommonLogicCriteriaBuilderException, RepositoryException,
       "Common LogicCriteriaBuilder exception");
DEF_EX(NullptrLogicCriteriaBuilderException, CommonLogicCriteriaBuilderException,
       "Null criteria occured");
DEF_EX(AllocationLogicCriteriaBuilderException, CommonLogicCriteriaBuilderException,
       "Unable to allocate criteria");

#endif

