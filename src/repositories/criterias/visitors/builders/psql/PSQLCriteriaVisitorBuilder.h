#ifndef _PSQLCRITERIAVISITORBUILDER_H_
#define _PSQLCRITERIAVISITORBUILDER_H_

#include "ICriteriaVisitorResultBuilder.h"
#include "CriteriaFieldMapper.h"
#include "CriteriaValueStringConverter.h"

class PSQLCriteriaVisitorBuilder : public ICriteriaVisitorResultBuilder<std::string>
{
    public:
        virtual ~PSQLCriteriaVisitorBuilder(void) override = default;
        virtual std::shared_ptr<ICriteriaVisitorResult<std::string>> get(void) const override;

        void setFieldMapper(std::shared_ptr<const CriteriaFieldMapper> mapper);
        void setValueConverter(std::shared_ptr<const CriteriaValueStringConverter> converter);

    private:
        std::shared_ptr<const CriteriaFieldMapper> mapper = nullptr;
        std::shared_ptr<const CriteriaValueStringConverter> converter = nullptr;

};

DEF_EX(CommonPSQLCriteriaVisitorBuilderException, CommonCriteriaVisitorResultBuilderException,
       "Common CriteriaVisitorResultBuilder Exception");
DEF_EX(NullptrPSQLCriteriaVisitorBuilderException, CommonCriteriaVisitorResultBuilderException,
       "Common CriteriaVisitorResultBuilder Exception");
DEF_EX(NotReadyPSQLCriteriaVisitorBuilderException, CommonCriteriaVisitorResultBuilderException,
       "Common CriteriaVisitorResultBuilder Exception");

#endif

