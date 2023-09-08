#ifndef _ICRITERIAVISITOR_H_
#define _ICRITERIAVISITOR_H_

#include "ICriteria.h"

class UnaryFieldCriteria;
class UnaryCompositeCriteria;
class ValueCriteria;
class FieldCriteria;
class CompositeCriteria;

class ICriteriaVisitor
{
    public:
        virtual ~ICriteriaVisitor(void) = default;

        virtual void visit(const UnaryFieldCriteria &criteria) = 0;
        virtual void visit(const UnaryCompositeCriteria &criteria) = 0;
        virtual void visit(const ValueCriteria &criteria) = 0;
        virtual void visit(const FieldCriteria &criteria) = 0;
        virtual void visit(const CompositeCriteria &criteria) = 0;
};

#endif

