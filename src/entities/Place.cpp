#include "Place.h"

Place::Place(void)
    : TimeChangeable(),
      id(this, &Place::setId, &Place::getId),
      type(this, &Place::setType, &Place::getType),
      name(this, &Place::setName, &Place::getName),
      area(this, &Place::setArea, &Place::getArea),
      continent(this, &Place::setContinent, &Place::getContinent)
{}

Place::Place(unsigned long long id, std::string type, std::string name,
             double area, std::string continent, std::time_t valid_from)
    : Place()
{
    this->_id = id;
    this->_type = type;
    this->_name = name;
    this->_area = area;
    this->_continent = continent;
    this->validFrom = valid_from;
}

Place::Place(const Place &place) : Place()
{
    this->_id = place._id;
    this->_type = place._type;
    this->_name = place._name;
    this->_area = place._area;
    this->_continent = place._continent;
    this->validFrom = place.validFrom;
}

Place &Place::operator = (const Place &place)
{
    this->_id = place._id;
    this->_type = place._type;
    this->_name = place._name;
    this->_area = place._area;
    this->_continent = place._continent;
    this->validFrom = place.validFrom;

    return *this;
}

