#ifndef _USERROLE_H_
#define _USERROLE_H_

#include <string>

#include "property.h"

class UserRole
{
    public:
        UserRole(void);
        UserRole(unsigned long long id, unsigned long long user_id,
                 std::string role);
        UserRole(const UserRole &ur);

        UserRole &operator = (const UserRole &ur);
        bool operator == (const UserRole &ur) const;
        bool operator != (const UserRole &ur) const;

        DEFAULT_SG(unsigned long long, Id, _id);
        DEFAULT_SG(unsigned long long, UserId, _user_id);
        DEFAULT_SG(std::string, Role, _role);

        Property<UserRole, unsigned long long> id;
        Property<UserRole, unsigned long long> userId;
        Property<UserRole, std::string> role;

    private:
        unsigned long long _id;
        unsigned long long _user_id;
        std::string _role;
};

#endif

