#ifndef _ITIMECHANGEABLE_H_
#define _ITIMECHANGEABLE_H_

#include <ctime>

#include "property.h"

class TimeChangeable
{
    public:
        TimeChangeable(void) : validFrom(this, &TimeChangeable::setTime, &TimeChangeable::getTime) {}
        virtual ~TimeChangeable(void) = default;

        DEFAULT_SG(std::time_t, Time, _time);

        Property<TimeChangeable, time_t> validFrom;

    private:
        std::time_t _time;
};

#endif

