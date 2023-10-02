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

std::string DateCommon::getTime(const std::time_t &time)
{
    std::string out = std::asctime(std::localtime(&time));

    return std::string(out.begin(), out.end() - 1);
}


std::time_t DateCommon::parseTime(std::string time, const char *const format)
{
    struct tm tm;
    tm.tm_isdst = -1; // auto determine
    time_t epoch = 0;

    if (strptime(time.c_str(), format, &tm) != NULL)
        epoch = mktime(&tm);

    return epoch;
}

