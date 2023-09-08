#include "HumanGeneral.h"

HumanGeneral::HumanGeneral(void)
    : TimeChangeable(),
      id(this, &HumanGeneral::setId, &HumanGeneral::getId),
      bloodType(this, &HumanGeneral::setBloodType, &HumanGeneral::getBloodType),
      gender(this, &HumanGeneral::setGender, &HumanGeneral::getGender),
      race(this, &HumanGeneral::setRace, &HumanGeneral::getRace)
{}

HumanGeneral::HumanGeneral(unsigned long long id, std::string blood_type,
                           std::string gender, std::string race,
                           std::time_t valid_from)
    : HumanGeneral()
{
    this->_id = id;
    this->_blood_type = blood_type;
    this->_gender = gender;
    this->_race = race;
    this->validFrom = valid_from;
}

HumanGeneral::HumanGeneral(const HumanGeneral &hg) : HumanGeneral()
{
    this->_id = hg._id;
    this->_blood_type = hg._blood_type;
    this->_gender = hg._gender;
    this->_race = hg._race;
    this->validFrom = hg.validFrom;
}

HumanGeneral &HumanGeneral::operator = (const HumanGeneral &hg)
{
    this->_id = hg._id;
    this->_blood_type = hg._blood_type;
    this->_gender = hg._gender;
    this->_race = hg._race;
    this->validFrom = hg.validFrom;

    return *this;
}

