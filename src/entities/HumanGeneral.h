#ifndef _HUMANGENERAL_H_
#define _HUMANGENERAL_H_

#include <string>

#include "property.h"

#include "TimeChangeable.h"

class HumanGeneral : public TimeChangeable
{
    public:
        HumanGeneral(void);
        HumanGeneral(unsigned long long id, std::string blood_type,
                     std::string gender, std::string race,
                     std::time_t valid_from);
        HumanGeneral(const HumanGeneral &hg);
        virtual ~HumanGeneral(void) = default;

        HumanGeneral &operator = (const HumanGeneral &hg);
        bool operator == (const HumanGeneral &hg) const;
        bool operator != (const HumanGeneral &hg) const;

        DEFAULT_SG(unsigned long long, Id, _id);
        DEFAULT_SG(std::string, BloodType, _blood_type);
        DEFAULT_SG(std::string, Gender, _gender);
        DEFAULT_SG(std::string, Race, _race);

        const std::time_t &getTime(void) const;

        Property<HumanGeneral, unsigned long long> id;
        Property<HumanGeneral, std::string> bloodType;
        Property<HumanGeneral, std::string> gender;
        Property<HumanGeneral, std::string> race;

    private:
        unsigned long long _id          = 0;
        std::string        _blood_type  = "none";
        std::string        _gender      = "none";
        std::string        _race        = "none";
};

#endif

