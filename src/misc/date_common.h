#ifndef _DATE_COMMON_H_
#define _DATE_COMMON_H_

#include <ctime>

namespace DateCommon
{
    const std::time_t max = 253402289999; // 9999-12-31 23:59:59

    bool valid(const std::time_t &time);
    int yearDiff(std::time_t start, std::time_t end);
}

#endif

