#include "FieldCriteria.h"
#include "ICriteriaVisitor.h"

FieldCriteria::FieldCriteria(void)
    : field1(this, &FieldCriteria::setField1, &FieldCriteria::getField1),
      op(this, &FieldCriteria::setOperator, &FieldCriteria::getOperator),
      field2(this, &FieldCriteria::setField2, &FieldCriteria::getField2)
{}

FieldCriteria::FieldCriteria(std::string field1, std::string op,
                             std::string field2)
    : FieldCriteria()
{
    this->_field1 = field1;
    this->_operator = op;
    this->_field2 = field2;
}

FieldCriteria::FieldCriteria(const FieldCriteria &criteria)
    : FieldCriteria()
{
    this->_field1 = criteria._field1;
    this->_operator = criteria._operator;
    this->_field2 = criteria._field2;
}

FieldCriteria &FieldCriteria::operator = (const FieldCriteria &criteria)
{
    this->_field1 = criteria._field1;
    this->_operator = criteria._operator;
    this->_field2 = criteria._field2;

    return *this;
}

void FieldCriteria::accept(ICriteriaVisitor &visitor) const
{
    visitor.visit(*this);
}

