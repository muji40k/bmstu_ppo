#include "date_common.h"

bool DateCommon::valid(const std::time_t &time)
{
    if (DateCommon::max < time)
        return false;

    if (0 > time)
        return false;

    return true;
}

int DateCommon::yearDiff(std::time_t start, std::time_t end)
{
    if (start > end)
    {
        std::time_t tmp = end;
        end = start;
        start = tmp;
    }

    const std::tm start_tm = *std::localtime(&start);
    const std::tm end_tm = *std::localtime(&end);

    int diff = end_tm.tm_year - start_tm.tm_year;

    if (start_tm.tm_yday < end_tm.tm_yday)
        return diff;
    else if (start_tm.tm_yday > end_tm.tm_yday)
        return --diff;

    if (start_tm.tm_hour < end_tm.tm_hour)
        return diff;
    else if (start_tm.tm_hour < end_tm.tm_hour)
        return --diff;

    if (start_tm.tm_min < end_tm.tm_min)
        return diff;
    else if (start_tm.tm_min > end_tm.tm_min)
        return --diff;

    if (start_tm.tm_sec <= end_tm.tm_sec)
        return diff;

    return --diff;
}

