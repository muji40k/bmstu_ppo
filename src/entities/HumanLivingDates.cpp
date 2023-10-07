#include "HumanLivingDates.h"

HumanLivingDates::HumanLivingDates(void)
    : TimeChangeable(),
      id(this, &HumanLivingDates::setId, &HumanLivingDates::getId),
      birthDate(this, &HumanLivingDates::setBirthDate, &HumanLivingDates::getBirthDate),
      deathDate(this, &HumanLivingDates::setDeathDate, &HumanLivingDates::getDeathDate)
{}

HumanLivingDates::HumanLivingDates(unsigned long long id, std::time_t birth_date,
                                   std::time_t valid_from)
    : HumanLivingDates()
{
    if (!DateCommon::valid(birth_date))
        throw CALL_EX(DateOverflowException);

    this->_id = id;
    this->_birth_date = birth_date;
    this->validFrom = valid_from;
}

HumanLivingDates::HumanLivingDates(unsigned long long id, std::time_t birth_date,
                                   std::time_t death_date, std::time_t valid_from)
    : HumanLivingDates()
{
    if (!DateCommon::valid(birth_date) || !DateCommon::valid(death_date))
        throw CALL_EX(DateOverflowException);

    if (birth_date > death_date)
        throw CALL_EX(DeathBeforeBirthException);

    this->_id = id;
    this->_birth_date = birth_date;
    this->_death_date = death_date;
    this->validFrom = valid_from;
}

HumanLivingDates::HumanLivingDates(const HumanLivingDates &hld)
    : HumanLivingDates()
{
    this->_id = hld._id;
    this->_birth_date = hld._birth_date;
    this->_death_date = hld._death_date;
    this->validFrom = hld.validFrom;
}

HumanLivingDates &HumanLivingDates::operator = (const HumanLivingDates &hld)
{
    this->_id = hld._id;
    this->_birth_date = hld._birth_date;
    this->_death_date = hld._death_date;
    this->validFrom = hld.validFrom;

    return *this;
}

bool HumanLivingDates::operator == (const HumanLivingDates &hld) const
{
    return this->_id == hld._id && this->validFrom == hld.validFrom;
}

bool HumanLivingDates::operator != (const HumanLivingDates &hld) const
{
    return this->_id != hld._id || this->validFrom != hld.validFrom;
}

void HumanLivingDates::setBirthDate(const std::time_t &time)
{
    if (!DateCommon::valid(time))
        throw CALL_EX(DateOverflowException);

    if (this->_death_date < time)
        throw CALL_EX(DeathBeforeBirthException);

    this->_birth_date = time;
}

void HumanLivingDates::setDeathDate(const std::time_t &time)
{
    if (!DateCommon::valid(time))
        throw CALL_EX(DateOverflowException);

    if (this->_birth_date > time)
        throw CALL_EX(DeathBeforeBirthException);

    this->_death_date = time;
}

const std::time_t &HumanLivingDates::getTime(void) const
{
    return this->TimeChangeable::getTime();
}

bool HumanLivingDates::isAlive(const std::time_t &date) const
{
    if (!DateCommon::valid(date))
        throw CALL_EX(DateOverflowException);

    return date < this->_death_date;
}

int HumanLivingDates::getAge(const std::time_t &date) const
{
    if (!DateCommon::valid(date))
        throw CALL_EX(DateOverflowException);

    if (this->_death_date < date)
        return DateCommon::yearDiff(this->_birth_date, this->_death_date);

    return DateCommon::yearDiff(this->_birth_date, date);
}

