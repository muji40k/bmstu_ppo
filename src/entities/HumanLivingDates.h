#ifndef _HUMANLIVINGDATES_H_
#define _HUMANLIVINGDATES_H_

#include "property.h"
#include "entity_exceptions.h"
#include "date_common.h"

#include "TimeChangeable.h"

class HumanLivingDates : public TimeChangeable
{
    public:
        HumanLivingDates(void);
        HumanLivingDates(unsigned long long id, std::time_t birth_date,
                         std::time_t valid_from);
        HumanLivingDates(unsigned long long id, std::time_t birth_date,
                         std::time_t death_date, std::time_t valid_from);
        HumanLivingDates(const HumanLivingDates &hld);
        virtual ~HumanLivingDates(void) = default;

        HumanLivingDates &operator = (const HumanLivingDates &hld);

        bool operator == (const HumanLivingDates &hld) const;
        bool operator != (const HumanLivingDates &hld) const;

        DEFAULT_SG(unsigned long long, Id, _id);

        void setBirthDate(const std::time_t &time);
        DEFAULT_GETTER(std::time_t, BirthDate, _birth_date);

        void setDeathDate(const std::time_t &time);
        DEFAULT_GETTER(std::time_t, DeathDate, _death_date);

        const std::time_t &getTime(void) const;

        Property<HumanLivingDates, unsigned long long> id;
        Property<HumanLivingDates, std::time_t> birthDate;
        Property<HumanLivingDates, std::time_t> deathDate;

        bool isAlive(const std::time_t &date) const;
        int getAge(const std::time_t &date) const;

    private:
        unsigned long long _id         = 0;
        std::time_t        _birth_date = 0;
        std::time_t        _death_date = DateCommon::max;
};

DEF_EX(CommonHumanLivingDatesException, EntityException,
       "Common HumanLivingDates exception");
DEF_EX(DeathBeforeBirthException, CommonHumanLivingDatesException,
       "Death can't occure before death");

#endif

