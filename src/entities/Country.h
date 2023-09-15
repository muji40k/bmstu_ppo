#ifndef _COUNTRY_H_
#define _COUNTRY_H_

#include <string>

#include "property.h"

#include "TimeChangeable.h"

class Country : public TimeChangeable
{
    public:
        Country(void);
        Country(unsigned long long id, std::string type, std::string name,
                double gdp, std::time_t valid_from);
        Country(const Country &country);
        virtual ~Country(void) = default;

        Country &operator = (const Country &country);

        bool operator == (const Country &country) const;
        bool operator != (const Country &country) const;

        DEFAULT_SG(unsigned long long, Id, _id);
        DEFAULT_SG(std::string, Type, _type);
        DEFAULT_SG(std::string, Name, _name);
        DEFAULT_SG(double, GDP, _gdp);

        const std::time_t &getTime(void) const;

        Property<Country, unsigned long long> id;
        Property<Country, std::string> type;
        Property<Country, std::string> name;
        Property<Country, double> gdp;

    private:
        unsigned long long _id   = 0;
        std::string        _type = "none";
        std::string        _name = "none";
        double             _gdp  = 0;
};

#endif

