#include "HumanSocial.h"

HumanSocial::HumanSocial(void)
    : TimeChangeable(),
      id(this, &HumanSocial::setId, &HumanSocial::getId),
      religion(this, &HumanSocial::setReligion, &HumanSocial::getReligion),
      wealth(this, &HumanSocial::setWealth, &HumanSocial::getWealth),
      literacy(this, &HumanSocial::setLiteracy, &HumanSocial::getLiteracy),
      busyness(this, &HumanSocial::setBusyness, &HumanSocial::getBusyness)
{}

HumanSocial::HumanSocial(unsigned long long id, std::string religion,
                         std::string wealth, std::string literacy,
                         std::string busyness, std::time_t valid_from)
    : HumanSocial()
{
    this->_id = id;
    this->_religion = religion;
    this->_wealth = wealth;
    this->_literacy = literacy;
    this->_busyness = busyness;
    this->validFrom = valid_from;
}

HumanSocial::HumanSocial(const HumanSocial &hc) : HumanSocial()
{
    this->_id = hc._id;
    this->_religion = hc._religion;
    this->_wealth = hc._wealth;
    this->_literacy = hc._literacy;
    this->_busyness = hc._busyness;
    this->validFrom = hc.validFrom;
}

HumanSocial &HumanSocial::operator = (const HumanSocial &hc)
{
    this->_id = hc._id;
    this->_religion = hc._religion;
    this->_wealth = hc._wealth;
    this->_literacy = hc._literacy;
    this->_busyness = hc._busyness;
    this->validFrom = hc.validFrom;

    return *this;
}

