#ifndef _UNARYCOMPOSITECRITERIA_H_
#define _UNARYCOMPOSITECRITERIA_H_

#include <string>

#include "property.h"

#include "ICriteria.h"

class UnaryCompositeCriteria : public ICriteria
{
    public:
        UnaryCompositeCriteria(const ICriteria &criteria, std::string op);
        UnaryCompositeCriteria(const UnaryCompositeCriteria &criteria);

        UnaryCompositeCriteria &operator = (const UnaryCompositeCriteria &criteria);

        virtual ~UnaryCompositeCriteria(void) override = default;
        virtual void accept(ICriteriaVisitor &visitor) const override;

        void setCriteria(const ICriteria &criteria);
        const ICriteria &getCriteria(void) const;
        DEFAULT_SG(std::string, Operator, _operator);

        Property<UnaryCompositeCriteria, ICriteria> criteria;
        Property<UnaryCompositeCriteria, std::string> op;

    private:
        UnaryCompositeCriteria(void);

        const ICriteria *_criteria;
        std::string      _operator = "";
};

#endif

