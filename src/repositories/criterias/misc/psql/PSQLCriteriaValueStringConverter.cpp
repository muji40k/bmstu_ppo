#include "PSQLCriteriaValueStringConverter.h"

PSQLCriteriaValueStringConverter::PSQLCriteriaValueStringConverter(std::list<std::shared_ptr<Item>> converters)
    : CriteriaValueStringConverter(converters)
{}

std::string PSQLCriteriaValueStringConverter::general(const std::string &value) const
{
    return '\'' + value + '\'';
}

