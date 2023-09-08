#ifndef _LANGUAGE_H_
#define _LANGUAGE_H_

#include <string>

#include "property.h"

#include "TimeChangeable.h"

class Language : public TimeChangeable
{
    public:
        Language(void);
        Language(unsigned long long id, std::string name, std::string family,
                 std::time_t valid_from);
        Language(const Language &language);
        virtual ~Language(void) = default;

        Language &operator = (const Language &language);

        bool operator < (const Language &language) const;

        DEFAULT_SG(unsigned long long, Id, _id);
        DEFAULT_SG(std::string, Name, _name);
        DEFAULT_SG(std::string, Family, _family);

        Property<Language, unsigned long long> id;
        Property<Language, std::string> name;
        Property<Language, std::string> family;

    private:
        unsigned long long _id   = 0;
        std::string        _name = "none";
        std::string        _family = "none";
};

#endif

