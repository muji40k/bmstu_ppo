#ifndef _VALUECRITERIA_H_
#define _VALUECRITERIA_H_

#include <string>

#include "property.h"

#include "ICriteria.h"

class ValueCriteria : public ICriteria
{
    public:
        ValueCriteria(void);
        ValueCriteria(std::string field, std::string op, std::string value);
        ValueCriteria(const ValueCriteria &criteria);

        ValueCriteria &operator = (const ValueCriteria &criteria);

        virtual ~ValueCriteria(void) override = default;
        virtual void accept(ICriteriaVisitor &visitor) const override;

        DEFAULT_SG(std::string, Field, _field);
        DEFAULT_SG(std::string, Operator, _operator);
        DEFAULT_SG(std::string, Value, _value);

        Property<ValueCriteria, std::string> field;
        Property<ValueCriteria, std::string> op;
        Property<ValueCriteria, std::string> value;

    private:
        std::string _field    = "";
        std::string _operator = "";
        std::string _value    = "";
};

#endif

