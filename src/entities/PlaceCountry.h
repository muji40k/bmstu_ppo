#ifndef _PLACECOUNTRY_H_
#define _PLACECOUNTRY_H_

#include "property.h"
#include "entity_exceptions.h"

#include "TimeChangeable.h"

#include "Country.h"

class PlaceCountry : public TimeChangeable
{
    public:
        PlaceCountry(void);
        PlaceCountry(unsigned long long id, Country country, time_t valid_from);
        PlaceCountry(const PlaceCountry &pc);
        virtual ~PlaceCountry(void) = default;

        PlaceCountry &operator = (const PlaceCountry &pc);

        virtual void setTime(const std::time_t &time) override;

        DEFAULT_SG(unsigned long long, Id, _id);
        void setCountry(const Country &country);
        DEFAULT_GETTER(Country, Country, _country);

        Property<PlaceCountry, unsigned long long> id;
        Property<PlaceCountry, Country> country;

    private:
        unsigned long long _id      = 0;
        Country            _country = Country();
};

#endif

