#ifndef _DATE_COMMON_H_
#define _DATE_COMMON_H_

#include <ctime>
#include <string>

namespace DateCommon
{
    const std::time_t max = 253402289999; // 9999-12-31 23:59:59

    bool valid(const std::time_t &time);
    int yearDiff(std::time_t start, std::time_t end);
    std::string getTime(const std::time_t &time);
    std::time_t parseTime(std::string time, const char *const format = "%Y-%m-%d %H:%M:%S");
}

#endif

