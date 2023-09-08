#ifndef _UNARYFIELDCRITERIA_H_
#define _UNARYFIELDCRITERIA_H_

#include <string>

#include "property.h"

#include "ICriteria.h"

class UnaryFieldCriteria : public ICriteria
{
    public:
        UnaryFieldCriteria(void);
        UnaryFieldCriteria(std::string field, std::string op);
        UnaryFieldCriteria(const UnaryFieldCriteria &criteria);

        UnaryFieldCriteria &operator = (const UnaryFieldCriteria &criteria);

        virtual ~UnaryFieldCriteria(void) override = default;
        virtual void accept(ICriteriaVisitor &visitor) const override;

        DEFAULT_SG(std::string, Field, _field);
        DEFAULT_SG(std::string, Operator, _operator);

        Property<UnaryFieldCriteria, std::string> field;
        Property<UnaryFieldCriteria, std::string> op;

    private:
        std::string _field    = "";
        std::string _operator = "";
};

#endif

