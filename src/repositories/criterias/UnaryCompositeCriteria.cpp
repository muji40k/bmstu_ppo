#include "UnaryCompositeCriteria.h"
#include "ICriteriaVisitor.h"

UnaryCompositeCriteria::UnaryCompositeCriteria(void)
    : criteria(this, &UnaryCompositeCriteria::setCriteria, &UnaryCompositeCriteria::getCriteria),
      op(this, &UnaryCompositeCriteria::setOperator, &UnaryCompositeCriteria::getOperator)
{}

UnaryCompositeCriteria::UnaryCompositeCriteria(const ICriteria &criteria, std::string op)
    : UnaryCompositeCriteria()
{
    this->_criteria = &criteria;
    this->_operator = op;
}

UnaryCompositeCriteria::UnaryCompositeCriteria(const UnaryCompositeCriteria &criteria)
    : UnaryCompositeCriteria()
{
    this->_criteria = criteria._criteria;
    this->_operator = criteria._operator;
}

UnaryCompositeCriteria &UnaryCompositeCriteria::operator = (const UnaryCompositeCriteria &criteria)
{
    this->_criteria = criteria._criteria;
    this->_operator = criteria._operator;

    return *this;
}

void UnaryCompositeCriteria::accept(ICriteriaVisitor &visitor) const
{
    visitor.visit(*this);
}

void UnaryCompositeCriteria::setCriteria(const ICriteria &criteria)
{
    this->_criteria = &criteria;
}

const ICriteria &UnaryCompositeCriteria::getCriteria(void) const
{
    return *this->_criteria;
}

