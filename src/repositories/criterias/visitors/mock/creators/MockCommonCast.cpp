#include <ctime>

#include "MockValueCriteriaMakers.hpp"

template <>
std::string MockValueCriteriaCaster::cast<std::string>(const std::string &value)
{
    return value;
}

template <>
unsigned long long MockValueCriteriaCaster::cast<unsigned long long>(const std::string &value)
{
    return std::stoull(value);
}

template <>
double MockValueCriteriaCaster::cast<double>(const std::string &value)
{
    return std::stod(value);
}

template <>
std::time_t MockValueCriteriaCaster::cast<std::time_t>(const std::string &value)
{
    return std::stoull(value);
}

