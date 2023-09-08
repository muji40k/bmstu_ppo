#include "UnaryFieldCriteria.h"
#include "ICriteriaVisitor.h"

UnaryFieldCriteria::UnaryFieldCriteria(void)
    : field(this, &UnaryFieldCriteria::setField, &UnaryFieldCriteria::getField),
      op(this, &UnaryFieldCriteria::setOperator, &UnaryFieldCriteria::getOperator)
{}

UnaryFieldCriteria::UnaryFieldCriteria(std::string field, std::string op)
    : UnaryFieldCriteria()
{
    this->_field = field;
    this->_operator = op;
}

UnaryFieldCriteria::UnaryFieldCriteria(const UnaryFieldCriteria &criteria)
    : UnaryFieldCriteria()
{
    this->_field = criteria._field;
    this->_operator = criteria._operator;
}

UnaryFieldCriteria &UnaryFieldCriteria::operator = (const UnaryFieldCriteria &criteria)
{
    this->_field = criteria._field;
    this->_operator = criteria._operator;

    return *this;
}

void UnaryFieldCriteria::accept(ICriteriaVisitor &visitor) const
{
    visitor.visit(*this);
}

