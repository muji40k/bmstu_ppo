#ifndef _USER_H_
#define _USER_H_

#include <string>

#include "property.h"

class User
{
    public:
        User(void);
        User(unsigned long long id, std::string name, std::string password,
             std::string email);
        User(const User &user);

        User &operator = (const User &user);
        bool operator < (const User &user);

        DEFAULT_SG(unsigned long long, Id, _id);
        DEFAULT_SG(std::string, Name, _name);
        DEFAULT_SG(std::string, Password, _password);
        DEFAULT_SG(std::string, Email, _email);

        Property<User, unsigned long long> id;
        Property<User, std::string> name;
        Property<User, std::string> password;
        Property<User, std::string> email;

    private:
        unsigned long long _id;
        std::string _name;
        std::string _password;
        std::string _email;
};

#endif

