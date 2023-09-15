#ifndef _MOCKCRITERIAINTERPRETER_HPP_
#define _MOCKCRITERIAINTERPRETER_HPP_

#include "MockCriteriaInterpreter.h"

#include "UnaryFieldCriteria.h"
#include "UnaryCompositeCriteria.h"
#include "ValueCriteria.h"
#include "FieldCriteria.h"
#include "CompositeCriteria.h"

#include "QueryableFilterGeneric.h"

#include "MockValueCriteriaMakers.hpp"
#include "MockCompositeCriteriaMakers.hpp"

template <typename Type>
void MockCriteriaInterpreter<Type>::visit(const UnaryFieldCriteria &)
{
    throw CALL_EX(UnsupportedMockCriteriaInterpreterException);
}

template <typename Type>
void MockCriteriaInterpreter<Type>::visit(const UnaryCompositeCriteria &criteria)
try
{
    if (criteria.op != std::string("not"))
        throw CALL_EX(UnsupportedMockCriteriaInterpreterException);

    criteria.criteria->accept(*this);

    std::shared_ptr<IQueryableFilter<Type>> out = std::make_shared<NotFilter<Type>>(*this->target);
    this->bank.push_back(out);
    this->target = out;
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationMockCriteriaInterpreterException);
}

template <typename Type>
void MockCriteriaInterpreter<Type>::visit(const ValueCriteria &criteria)
try
{
    std::shared_ptr<IQueryableFilter<Type>> out = MockValueCriteriaMakers<Type>::get(criteria);

    if (nullptr == out)
        throw CALL_EX(UnsupportedMockCriteriaInterpreterException);

    this->bank.push_back(out);
    this->target = out;
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationMockCriteriaInterpreterException);
}

template <typename Type>
void MockCriteriaInterpreter<Type>::visit(const FieldCriteria &)
{
    throw CALL_EX(UnsupportedMockCriteriaInterpreterException);
}

template <typename Type>
void MockCriteriaInterpreter<Type>::visit(const CompositeCriteria &criteria)
try
{
    criteria.criteria1->accept(*this);
    std::shared_ptr<IQueryableFilter<Type>> c1 = this->target;

    criteria.criteria2->accept(*this);
    std::shared_ptr<IQueryableFilter<Type>> c2 = this->target;

    std::shared_ptr<IQueryableFilter<Type>> out = \
        MockCompositeCriteriaMaker<Type>::get(*c1, criteria.op, *c2);

    if (nullptr == out)
        throw CALL_EX(UnsupportedMockCriteriaInterpreterException);

    this->bank.push_back(out);
    this->target = out;
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationMockCriteriaInterpreterException);
}

template <typename Type>
const std::shared_ptr<IQueryableFilter<Type>> &MockCriteriaInterpreter<Type>::result(void) const
{
    return this->target;
}

#endif

