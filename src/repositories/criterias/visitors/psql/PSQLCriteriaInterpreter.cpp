#include "PSQLCriteriaInterpreter.h"

#include "UnaryFieldCriteria.h"
#include "UnaryCompositeCriteria.h"
#include "ValueCriteria.h"
#include "FieldCriteria.h"
#include "CompositeCriteria.h"

PSQLCriteriaInterpreter::PSQLCriteriaInterpreter(const CriteriaFieldMapper &mapper,
                                                 const CriteriaValueStringConverter &converter)
    : mapper(mapper), converter(converter)
{}

void PSQLCriteriaInterpreter::visit(const UnaryFieldCriteria &criteria)
{
    this->res = std::string("(")
                + criteria.op + " "
                + this->mapper.get(criteria.field)
                + ")";
}

void PSQLCriteriaInterpreter::visit(const UnaryCompositeCriteria &criteria)
{
    criteria.criteria->accept(*this);
    this->res = std::string("(")
                + criteria.op + " "
                + this->res
                + ")";
}

void PSQLCriteriaInterpreter::visit(const ValueCriteria &criteria)
{
    this->res = std::string("(")
                + this->mapper.get(criteria.field) + " "
                + criteria.op + " "
                + this->converter.convert(criteria.field, criteria.value) + ")";
}

void PSQLCriteriaInterpreter::visit(const FieldCriteria &criteria)
{
    this->res = std::string("(")
                + this->mapper.get(criteria.field1) + " "
                + criteria.op + " "
                + this->mapper.get(criteria.field2)
                + ")";
}

void PSQLCriteriaInterpreter::visit(const CompositeCriteria &criteria)
{
    std::string out = "(";
    criteria.criteria1->accept(*this);
    out += this->res + " "
           + criteria.op + " ";
    criteria.criteria2->accept(*this);
    out += this->res + ")";

    this->res = out;
}

const std::string &PSQLCriteriaInterpreter::result(void) const
{
    return res;
}

