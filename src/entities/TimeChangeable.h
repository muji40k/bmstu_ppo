#ifndef _ITIMECHANGEABLE_H_
#define _ITIMECHANGEABLE_H_

#include <ctime>

#include "property.h"
#include "entity_exceptions.h"

class TimeChangeable
{
    public:
        TimeChangeable(void);
        virtual ~TimeChangeable(void) = 0;

        virtual void setTime(const std::time_t &time);
        DEFAULT_GETTER(std::time_t, Time, _time);

        Property<TimeChangeable, time_t> validFrom;

    private:
        std::time_t _time = 0;
};

#endif

