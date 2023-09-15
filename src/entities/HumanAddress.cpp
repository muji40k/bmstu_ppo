#include "HumanAddress.h"

HumanAddress::HumanAddress(void)
    : TimeChangeable(),
      id(this, &HumanAddress::setId, &HumanAddress::getId),
      currentPlace(this, &HumanAddress::setCurrentPlace, &HumanAddress::getCurrentPlace)
{}

HumanAddress::HumanAddress(unsigned long long id, Place address,
                           time_t valid_from)
    : HumanAddress()
{
    this->_id = id;
    this->_address = address;
    this->validFrom = valid_from;
}

HumanAddress::HumanAddress(const HumanAddress &ha) : HumanAddress()
{
    this->_id = ha._id;
    this->_address = ha._address;
    this->validFrom = ha.validFrom;
}

HumanAddress &HumanAddress::operator = (const HumanAddress &ha)
{
    this->_id = ha._id;
    this->_address = ha._address;
    this->validFrom = ha.validFrom;

    return *this;
}

bool HumanAddress::operator == (const HumanAddress &ha) const
{
    return this->_id == ha._id && this->validFrom == ha.validFrom;
}

bool HumanAddress::operator != (const HumanAddress &ha) const
{
    return this->_id != ha._id || this->validFrom != ha.validFrom;
}

void HumanAddress::setTime(const std::time_t &time)
{
    if (time < this->_address.validFrom)
        throw CALL_EX(ChronologicalException);

    this->TimeChangeable::setTime(time);
}

const std::time_t &HumanAddress::getTime(void) const
{
    return this->TimeChangeable::getTime();
}

void HumanAddress::setCurrentPlace(const Place &place)
{
    if (place.validFrom > this->validFrom)
        throw CALL_EX(ChronologicalException);

    this->_address = place;
}

