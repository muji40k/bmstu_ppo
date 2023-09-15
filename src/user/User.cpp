#include "User.h"

User::User(void)
    : id(this, &User::setId, &User::getId),
      name(this, &User::setName, &User::getName),
      password(this, &User::setPassword, &User::getPassword),
      email(this, &User::setEmail, &User::getEmail)
{}

User::User(unsigned long long id, std::string name, std::string password,
           std::string email)
    : User()
{
    this->_id = id;
    this->_name = name;
    this->_password = password;
    this->_email = email;
}

User::User(const User &user) : User()
{
    this->_id = user._id;
    this->_name = user._name;
    this->_password = user._password;
    this->_email = user._email;
}

User &User::operator = (const User &user)
{
    this->_id = user._id;
    this->_name = user._name;
    this->_password = user._password;
    this->_email = user._email;

    return *this;
}

bool User::operator < (const User &user)
{
    return this->_id < user._id;
}

bool User::operator == (const User &user) const
{
    return this->_id == user._id;
}

bool User::operator != (const User &user) const
{
    return this->_id != user._id;
}

