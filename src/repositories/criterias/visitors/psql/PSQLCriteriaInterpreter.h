#ifndef _PSQLCRITERIAINTERPRETER_H_
#define _PSQLCRITERIAINTERPRETER_H_

#include "ICriteriaVisitorResult.h"

#include "CriteriaFieldMapper.h"
#include "CriteriaValueStringConverter.h"

class PSQLCriteriaInterpreter : public ICriteriaVisitorResult<std::string>
{
    public:
        PSQLCriteriaInterpreter(const CriteriaFieldMapper &mapper,
                                const CriteriaValueStringConverter &converter);
        virtual ~PSQLCriteriaInterpreter(void) override = default;

        virtual void visit(const UnaryFieldCriteria &criteria) override;
        virtual void visit(const UnaryCompositeCriteria &criteria) override;
        virtual void visit(const ValueCriteria &criteria) override;
        virtual void visit(const FieldCriteria &criteria) override;
        virtual void visit(const CompositeCriteria &criteria) override;

        virtual const std::string &result(void) const override;

    private:
        const CriteriaFieldMapper &mapper;
        const CriteriaValueStringConverter &converter;
        std::string res;
};

#endif

