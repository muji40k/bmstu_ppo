#ifndef _MOCKCRITERIAINTERPRETER_H_
#define _MOCKCRITERIAINTERPRETER_H_

#include <memory>
#include <list>

#include "ICriteriaVisitor.h"
#include "ICriteriaVisitorResult.h"

#include "IQueryable.h"

template <typename Type>
class MockCriteriaInterpreter : public ICriteriaVisitor,
                                public ICriteriaVisitorResult<std::shared_ptr<IQueryableFilter<Type>>>
{
    public:
        virtual ~MockCriteriaInterpreter(void) override = default;

        virtual void visit(const UnaryFieldCriteria &criteria) override;
        virtual void visit(const UnaryCompositeCriteria &criteria) override;
        virtual void visit(const ValueCriteria &criteria) override;
        virtual void visit(const FieldCriteria &criteria) override;
        virtual void visit(const CompositeCriteria &criteria) override;

        virtual const std::shared_ptr<IQueryableFilter<Type>> &result(void) const override;

    private:
        std::list<std::shared_ptr<IQueryableFilter<Type>>> bank;
        std::shared_ptr<IQueryableFilter<Type>> target = nullptr;
};

DEF_EX(AllocationMockCriteriaInterpreterException, CommonCriteriaVisitorException,
       "Allocation mock visitor error");
DEF_EX(UnsupportedMockCriteriaInterpreterException, CommonCriteriaVisitorException,
       "Given criteria is unsupported with mock visitor");

#include "MockCriteriaInterpreter.hpp"

#endif

