#ifndef _FIELDCRITERIA_H_
#define _FIELDCRITERIA_H_

#include <string>

#include "property.h"

#include "ICriteria.h"

class FieldCriteria : public ICriteria
{
    public:
        FieldCriteria(void);
        FieldCriteria(std::string field1, std::string op, std::string field2);
        FieldCriteria(const FieldCriteria &criteria);

        FieldCriteria &operator = (const FieldCriteria &criteria);

        virtual ~FieldCriteria(void) = default;
        virtual void accept(ICriteriaVisitor &visitor) const override;

        DEFAULT_SG(std::string, Field1, _field1);
        DEFAULT_SG(std::string, Operator, _operator);
        DEFAULT_SG(std::string, Field2, _field2);

        Property<FieldCriteria, std::string> field1;
        Property<FieldCriteria, std::string> op;
        Property<FieldCriteria, std::string> field2;

    private:
        std::string _field1   = "";
        std::string _operator = "";
        std::string _field2   = "";
};

#endif

