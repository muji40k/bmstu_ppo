#ifndef _HUMAN_H_
#define _HUMAN_H_

#include <string>

#include "property.h"
#include "entity_exceptions.h"

#include "TimeChangeable.h"

#include "Place.h"

class Human : public TimeChangeable
{
    public:
        Human(void);
        Human(unsigned long long id, std::string first_name,
              std::string last_name, Place birth_place, time_t valid_from);
        Human(unsigned long long id, std::string first_name,
              std::string last_name, std::string patronymic, Place birth_place,
              time_t valid_from);
        Human(const Human &human);
        virtual ~Human(void) = default;

        Human &operator = (const Human &human);
        bool operator == (const Human &human) const;
        bool operator != (const Human &human) const;

        const std::time_t &getTime(void) const;
        virtual void setTime(const std::time_t &time) override;

        DEFAULT_SG(unsigned long long, Id, _id);
        DEFAULT_SG(std::string, FirstName, _fname);
        DEFAULT_SG(std::string, LastName, _lname);
        const std::string &getPatronymic(void) const;
        void setPatronymic(const std::string &value);
        void setBirthPlace(const Place &place);
        DEFAULT_GETTER(Place, BirthPlace, _birth_place);

        bool isPatronymic(void) const;
        void setIsPatronymic(bool state);

        Property<Human, unsigned long long> id;
        Property<Human, std::string> firstName;
        Property<Human, std::string> lastName;
        Property<Human, std::string> patronymic;
        Property<Human, Place> birthPlace;

    private:
        unsigned long long _id            = 0;
        std::string        _fname         = "none";
        std::string        _lname         = "none";
        bool               _is_patronymic = false;
        std::string        _patronymic    = "none";
        Place              _birth_place   = Place();
};

DEF_EX(CommonHumanException, EntityException, "Common Human exception");
DEF_EX(NoPatronymicException, CommonHumanException,
       "Human doesn't have patronymic");

#endif

