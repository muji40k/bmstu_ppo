#include "Human.h"

Human::Human(void)
    : TimeChangeable(),
      id(this, &Human::setId, &Human::getId),
      firstName(this, &Human::setFirstName, &Human::getFirstName),
      lastName(this, &Human::setLastName, &Human::getLastName),
      patronymic(this, &Human::setPatronymic, &Human::getPatronymic),
      birthPlace(this, &Human::setBirthPlace, &Human::getBirthPlace)
{}

Human::Human(unsigned long long id, std::string first_name,
             std::string last_name, Place birth_place, time_t valid_from)
    : Human()
{
    this->_id = id;
    this->_fname = first_name;
    this->_lname = last_name;
    this->_birth_place = birth_place;
    this->validFrom = valid_from;
}

Human::Human(unsigned long long id, std::string first_name,
             std::string last_name, std::string patronymic, Place birth_place,
             time_t valid_from)
    : Human(id, first_name, last_name, birth_place, valid_from)
{
    this->_is_patronymic = true;
    this->_patronymic = patronymic;
}

Human::Human(const Human &human) : Human()
{
    this->_id = human._id;
    this->_fname = human._fname;
    this->_lname = human._lname;
    this->_birth_place = human._birth_place;
    this->validFrom = human.validFrom;
    this->_is_patronymic = human._is_patronymic;
    this->_patronymic = human._patronymic;
}

Human &Human::operator = (const Human &human)
{
    this->_id = human._id;
    this->_fname = human._fname;
    this->_lname = human._lname;
    this->_birth_place = human._birth_place;
    this->validFrom = human.validFrom;
    this->_is_patronymic = human._is_patronymic;
    this->_patronymic = human._patronymic;

    return *this;
}

bool Human::operator == (const Human &human) const
{
    return this->_id == human._id && this->validFrom == human.validFrom;
}

bool Human::operator != (const Human &human) const
{
    return this->_id != human._id || this->validFrom != human.validFrom;
}

const std::time_t &Human::getTime(void) const
{
    return this->TimeChangeable::getTime();
}

void Human::setTime(const std::time_t &time)
{
    if (time < this->_birth_place.validFrom)
        throw CALL_EX(ChronologicalException);

    this->TimeChangeable::setTime(time);
}

const std::string &Human::getPatronymic(void) const
{
    if (!this->isPatronymic())
        throw CALL_EX(NoPatronymicException);

    return this->_patronymic;
}

void Human::setPatronymic(const std::string &value)
{
    if (!this->isPatronymic())
        throw CALL_EX(NoPatronymicException);

    this->_patronymic = value;
}

void Human::setBirthPlace(const Place &place)
{
    if (place.validFrom > this->validFrom)
        throw CALL_EX(ChronologicalException);

    this->_birth_place = place;
}

bool Human::isPatronymic(void) const
{
    return this->_is_patronymic;
}

void Human::setIsPatronymic(bool state)
{
    this->_is_patronymic = state;
}

