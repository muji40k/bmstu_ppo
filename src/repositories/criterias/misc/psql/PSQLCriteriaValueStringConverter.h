#ifndef _PSQLCRITERIAVALUESTRINGCONVERTER_H_
#define _PSQLCRITERIAVALUESTRINGCONVERTER_H_

#include "CriteriaValueStringConverter.h"

class PSQLCriteriaValueStringConverter : public CriteriaValueStringConverter
{
    public:
        PSQLCriteriaValueStringConverter(std::list<std::shared_ptr<Item>> converters);
        virtual ~PSQLCriteriaValueStringConverter(void) override = default;

    private:
        virtual std::string general(const std::string &value) const override;
};

#endif

