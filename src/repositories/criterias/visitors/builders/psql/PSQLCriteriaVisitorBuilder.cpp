#include "PSQLCriteriaVisitorBuilder.h"

#include "PSQLCriteriaInterpreter.h"

std::shared_ptr<ICriteriaVisitorResult<std::string>> PSQLCriteriaVisitorBuilder::get(void) const
{
    if (nullptr == this->mapper || nullptr == this->converter)
        throw CALL_EX(NotReadyPSQLCriteriaVisitorBuilderException);

    return std::make_shared<PSQLCriteriaInterpreter>(*this->mapper, *this->converter);
}

void PSQLCriteriaVisitorBuilder::setFieldMapper(std::shared_ptr<const CriteriaFieldMapper> mapper)
{
    if (nullptr == mapper)
        throw CALL_EX(NullptrPSQLCriteriaVisitorBuilderException);

    this->mapper = mapper;
}

void PSQLCriteriaVisitorBuilder::setValueConverter(std::shared_ptr<const CriteriaValueStringConverter> converter)
{
    if (nullptr == converter)
        throw CALL_EX(NullptrPSQLCriteriaVisitorBuilderException);

    this->converter = converter;
}

