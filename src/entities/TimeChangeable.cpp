#include "TimeChangeable.h"

#include "date_common.h"

TimeChangeable::TimeChangeable(void)
    : validFrom(this, &TimeChangeable::setTime, &TimeChangeable::getTime)
{}

TimeChangeable::~TimeChangeable(void) {}

void TimeChangeable::setTime(const std::time_t &time)
{
    if (!DateCommon::valid(time))
        throw CALL_EX(DateOverflowException);

    this->_time = time;
}

