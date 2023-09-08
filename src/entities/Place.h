#ifndef _PLACE_H_
#define _PLACE_H_

#include <string>

#include "property.h"

#include "TimeChangeable.h"

class Place : public TimeChangeable
{
    public:
        Place(void);
        Place(unsigned long long id, std::string type, std::string name,
              double area, std::string continent, std::time_t valid_from);
        Place(const Place &place);
        virtual ~Place(void) = default;

        Place &operator = (const Place &place);

        DEFAULT_SG(unsigned long long, Id, _id);
        DEFAULT_SG(std::string, Type, _type);
        DEFAULT_SG(std::string, Name, _name);
        DEFAULT_SG(double, Area, _area);
        DEFAULT_SG(std::string, Continent, _continent);

        Property<Place, unsigned long long> id;
        Property<Place, std::string> type;
        Property<Place, std::string> name;
        Property<Place, double> area;
        Property<Place, std::string> continent;

    private:
        unsigned long long _id        = 0;
        std::string        _type      = "none";
        std::string        _name      = "none";
        double             _area      = 0;
        std::string        _continent = "none";
};

#endif

