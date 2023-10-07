#include "PlaceCountry.h"

PlaceCountry::PlaceCountry(void)
    : TimeChangeable(),
      id(this, &PlaceCountry::setId, &PlaceCountry::getId),
      country(this, &PlaceCountry::setCountry, &PlaceCountry::getCountry)
{}

PlaceCountry::PlaceCountry(unsigned long long id, Country country,
                           time_t valid_from)
    : PlaceCountry()
{
    this->_id = id;
    this->_country = country;
    this->validFrom = valid_from;
}

PlaceCountry::PlaceCountry(const PlaceCountry &pc) : PlaceCountry()
{
    this->_id = pc._id;
    this->_country = pc._country;
    this->validFrom = pc.validFrom;
}

PlaceCountry &PlaceCountry::operator = (const PlaceCountry &pc)
{
    this->_id = pc._id;
    this->_country = pc._country;
    this->validFrom = pc.validFrom;

    return *this;
}

bool PlaceCountry::operator == (const PlaceCountry &pc) const
{
    return this->_id == pc._id && this->validFrom == pc.validFrom;
}

bool PlaceCountry::operator != (const PlaceCountry &pc) const
{
    return this->_id != pc._id || this->validFrom != pc.validFrom;
}

void PlaceCountry::setTime(const std::time_t &time)
{
    if (time < this->_country.validFrom)
        throw CALL_EX(ChronologicalException);

    this->TimeChangeable::setTime(time);
}

const std::time_t &PlaceCountry::getTime(void) const
{
    return this->TimeChangeable::getTime();
}

void PlaceCountry::setCountry(const Country &country)
{
    if (country.validFrom > this->validFrom)
        throw CALL_EX(ChronologicalException);

    this->_country = country;
}

