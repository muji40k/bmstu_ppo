#include "Resource.h"

Resource::Resource(void)
    : TimeChangeable(),
      id(this, &Resource::setId, &Resource::getId),
      type(this, &Resource::setType, &Resource::getType),
      name(this, &Resource::setName, &Resource::getName),
      value(this, &Resource::setValue, &Resource::getValue),
      rarity(this, &Resource::setRarity, &Resource::getRarity)
{}

Resource::Resource(unsigned long long id, std::string type, std::string name,
                   double value, std::string rarity, std::time_t valid_from)
    : Resource()
{
    this->_id = id;
    this->_type = type;
    this->_name = name;
    this->_value = value;
    this->_rarity = rarity;
    this->validFrom = valid_from;
}

Resource::Resource(const Resource &resource) : Resource()
{
    this->_id = resource._id;
    this->_type = resource._type;
    this->_name = resource._name;
    this->_value = resource._value;
    this->_rarity = resource._rarity;
    this->validFrom = resource.validFrom;
}

Resource &Resource::operator = (const Resource &resource)
{
    this->_id = resource._id;
    this->_type = resource._type;
    this->_name = resource._name;
    this->_value = resource._value;
    this->_rarity = resource._rarity;
    this->validFrom = resource.validFrom;

    return *this;
}

bool Resource::operator < (const Resource &resource) const
{
    return this->_id < resource._id;
}

