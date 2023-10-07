#include "LogicCriteriaBuilder.h"

#include "UnaryCompositeCriteria.h"

LogicCriteriaBuilder::LogicCriteriaBuilder(std::shared_ptr<const ICriteria> start, bool inv)
{
    if (nullptr == start)
        throw CALL_EX(NullptrLogicCriteriaBuilderException);

   this->target = this->addCurrent(start, inv);
}

std::shared_ptr<const ICriteria> LogicCriteriaBuilder::get(void) const
{
    return this->target;
}

void LogicCriteriaBuilder::addAND(std::shared_ptr<const ICriteria> criteria, bool inv)
{
    if (nullptr == criteria)
        throw CALL_EX(NullptrLogicCriteriaBuilderException);

    this->add("and", criteria, inv);
}

void LogicCriteriaBuilder::addOR(std::shared_ptr<const ICriteria> criteria, bool inv)
{
    if (nullptr == criteria)
        throw CALL_EX(NullptrLogicCriteriaBuilderException);

    this->add("or", criteria, inv);
}

std::shared_ptr<const ICriteria> LogicCriteriaBuilder::addCurrent(std::shared_ptr<const ICriteria> criteria, bool inv)
try
{
    std::shared_ptr<const ICriteria> current = criteria;

    if (inv)
    {
        this->not_bank.push_front(criteria);
        current = std::make_shared<UnaryCompositeCriteria>(*criteria, "not");
    }

    this->main_bank.push_front(current);

    return current;
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationLogicCriteriaBuilderException);
}

void LogicCriteriaBuilder::add(std::string op, std::shared_ptr<const ICriteria> current, bool inv)
try
{
    std::shared_ptr<const ICriteria> previous = this->main_bank.front();
    current = this->addCurrent(current, inv);
    std::shared_ptr<CompositeCriteria> composite = std::make_shared<CompositeCriteria>(*previous, op, *current);

    if (!this->composite_bank.empty())
        this->composite_bank.front()->criteria2 = *composite;
    else
        this->target = composite;

    this->composite_bank.push_front(composite);
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationLogicCriteriaBuilderException);
}

