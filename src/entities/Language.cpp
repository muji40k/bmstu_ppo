#include "Language.h"

Language::Language(void)
    : TimeChangeable(),
      id(this, &Language::setId, &Language::getId),
      name(this, &Language::setName, &Language::getName),
      family(this, &Language::setFamily, &Language::getFamily)
{}

Language::Language(unsigned long long id, std::string name, std::string family,
                   std::time_t valid_from)
    : Language()
{
    this->_id = id;
    this->_name = name;
    this->_family = family;
    this->validFrom = valid_from;
}

Language::Language(const Language &language) : Language()
{
    this->_id = language._id;
    this->_name = language._name;
    this->_family = language._family;
    this->validFrom = language.validFrom;
}

Language &Language::operator = (const Language &language)
{
    this->_id = language._id;
    this->_name = language._name;
    this->_family = language._family;
    this->validFrom = language.validFrom;

    return *this;
}

bool Language::operator < (const Language &language) const
{
    return this->_id < language._id;
}

