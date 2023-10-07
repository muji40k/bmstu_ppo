#include "ValueCriteria.h"
#include "ICriteriaVisitor.h"

ValueCriteria::ValueCriteria(void)
    : field(this, &ValueCriteria::setField, &ValueCriteria::getField),
      op(this, &ValueCriteria::setOperator, &ValueCriteria::getOperator),
      value(this, &ValueCriteria::setValue, &ValueCriteria::getValue)
{}

ValueCriteria::ValueCriteria(std::string field, std::string op, std::string value)
    : ValueCriteria()
{
    this->_field = field;
    this->_operator = op;
    this->_value = value;
}

ValueCriteria::ValueCriteria(const ValueCriteria &criteria)
    : ValueCriteria()
{
    this->_field = criteria._field;
    this->_operator = criteria._operator;
    this->_value = criteria._value;
}

ValueCriteria &ValueCriteria::operator = (const ValueCriteria &criteria)
{
    this->_field = criteria._field;
    this->_operator = criteria._operator;
    this->_value = criteria._value;

    return *this;
}

void ValueCriteria::accept(ICriteriaVisitor &visitor) const
{
    visitor.visit(*this);
}

