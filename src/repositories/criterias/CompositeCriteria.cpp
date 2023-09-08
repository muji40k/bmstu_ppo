#include "CompositeCriteria.h"
#include "ICriteriaVisitor.h"

CompositeCriteria::CompositeCriteria(void)
    : criteria1(this, &CompositeCriteria::setCriteria1, &CompositeCriteria::getCriteria1),
      op(this, &CompositeCriteria::setOperator, &CompositeCriteria::getOperator),
      criteria2(this, &CompositeCriteria::setCriteria2, &CompositeCriteria::getCriteria2)
{}

CompositeCriteria::CompositeCriteria(const ICriteria &criteria1, std::string op,
                                     const ICriteria &criteria2)
    : CompositeCriteria()
{
    this->_criteria1 = &criteria1;
    this->_operator  = op;
    this->_criteria2 = &criteria2;
}

CompositeCriteria::CompositeCriteria(const CompositeCriteria &criteria)
    : CompositeCriteria()
{
    this->_criteria1 = criteria._criteria1;
    this->_operator  = criteria._operator;
    this->_criteria2 = criteria._criteria2;
}

CompositeCriteria &CompositeCriteria::operator = (const CompositeCriteria &criteria)
{
    this->_criteria1 = criteria._criteria1;
    this->_operator  = criteria._operator;
    this->_criteria2 = criteria._criteria2;

    return *this;
}

void CompositeCriteria::accept(ICriteriaVisitor &visitor) const
{
    visitor.visit(*this);
}

void CompositeCriteria::setCriteria1(const ICriteria &criteria)
{
    this->_criteria1 = &criteria;
}

const ICriteria &CompositeCriteria::getCriteria1(void) const
{
    return *this->_criteria1;
}

void CompositeCriteria::setCriteria2(const ICriteria &criteria)
{
        this->_criteria2 = &criteria;
}

const ICriteria &CompositeCriteria::getCriteria2(void) const
{
        return *this->_criteria2;
}

