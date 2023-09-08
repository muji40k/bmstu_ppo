#include "string_common.h"

#include <cctype>
#include <algorithm>

static unsigned char wrap(unsigned char c)
{
    return std::tolower(c); 
}

std::string StringCommon::to_lower(const std::string &string)
{
    std::string s = string;
    std::transform(s.begin(), s.end(), s.begin(), wrap);

    return s;
}

