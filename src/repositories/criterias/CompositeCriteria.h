#ifndef _COMPOSITECRITERIA_H_
#define _COMPOSITECRITERIA_H_

#include <string>

#include "property.h"

#include "ICriteria.h"

class CompositeCriteria : public ICriteria
{
    public:
        CompositeCriteria(const ICriteria &criteria1, std::string op,
                          const ICriteria &criteria2);
        CompositeCriteria(const CompositeCriteria &criteria);

        CompositeCriteria &operator = (const CompositeCriteria &criteria);

        virtual ~CompositeCriteria(void) override = default;
        virtual void accept(ICriteriaVisitor &visitor) const override;

        void setCriteria1(const ICriteria &criteria);
        const ICriteria &getCriteria1(void) const;
        DEFAULT_SG(std::string, Operator, _operator);
        void setCriteria2(const ICriteria &criteria);
        const ICriteria &getCriteria2(void) const;

        Property<CompositeCriteria, ICriteria> criteria1;
        Property<CompositeCriteria, std::string> op;
        Property<CompositeCriteria, ICriteria> criteria2;

    private:
        CompositeCriteria(void);

        const ICriteria *_criteria1;
        std::string      _operator = "";
        const ICriteria *_criteria2;
};

#endif

