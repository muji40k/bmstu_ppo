#include "Country.h"

Country::Country(void)
    : TimeChangeable(),
      id(this, &Country::setId, &Country::getId),
      type(this, &Country::setType, &Country::getType),
      name(this, &Country::setName, &Country::getName),
      gdp(this, &Country::setGDP, &Country::getGDP)
{}

Country::Country(unsigned long long id, std::string type, std::string name,
                 double gdp, std::time_t valid_from)
    : Country()
{
    this->_id = id;
    this->_type = type;
    this->_name = name;
    this->_gdp = gdp;
    this->validFrom = valid_from;
}

Country::Country(const Country &country) : Country()
{
    this->_id = country._id;
    this->_type = country._type;
    this->_name = country._name;
    this->_gdp = country._gdp;
    this->validFrom = country.validFrom;
}

Country &Country::operator = (const Country &country)
{
    this->_id = country._id;
    this->_type = country._type;
    this->_name = country._name;
    this->_gdp = country._gdp;
    this->validFrom = country.validFrom;

    return *this;
}

bool Country::operator == (const Country &country) const
{
    return this->_id == country._id && this->validFrom == country.validFrom;
}

bool Country::operator != (const Country &country) const
{
    return this->_id != country._id || this->validFrom != country.validFrom;
}

const std::time_t &Country::getTime(void) const
{
    return this->TimeChangeable::getTime();
}

