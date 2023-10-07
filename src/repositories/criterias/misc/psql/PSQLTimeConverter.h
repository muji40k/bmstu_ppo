#ifndef _PSQLTIMECONVERTER_H_
#define _PSQLTIMECONVERTER_H_

#include "CriteriaValueStringConverter.h"

class PSQLTimeConverter : public CriteriaValueStringConverter::Item
{
    public:
        PSQLTimeConverter(std::string type);
        virtual ~PSQLTimeConverter(void) override = default;
        virtual const std::string &type(void) const override ;
        virtual std::string apply(const std::string &value) override;

    private:
        const std::string name;
};

#endif

