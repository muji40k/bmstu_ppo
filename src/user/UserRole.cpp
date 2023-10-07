#include "UserRole.h"

UserRole::UserRole(void)
    : id(this, &UserRole::setId, &UserRole::getId),
      userId(this, &UserRole::setUserId, &UserRole::getUserId),
      role(this, &UserRole::setRole, &UserRole::getRole)
{}

UserRole::UserRole(unsigned long long id, unsigned long long user_id,
                   std::string role)
    : UserRole()
{
    this->_id = id;
    this->_user_id = user_id;
    this->_role = role;
}

UserRole::UserRole(const UserRole &ur) : UserRole()
{
    this->_id = ur._id;
    this->_user_id = ur._user_id;
    this->_role = ur._role;
}

UserRole &UserRole::operator = (const UserRole &ur)
{
    this->_id = ur._id;
    this->_user_id = ur._user_id;
    this->_role = ur._role;

    return *this;
}

bool UserRole::operator == (const UserRole &ur) const
{
    return this->_id == ur._id;
}

bool UserRole::operator != (const UserRole &ur) const
{
    return this->_id != ur._id;
}

