#include "PSQLTimeConverter.h"

PSQLTimeConverter::PSQLTimeConverter(std::string type)
    : name(type)
{}

const std::string &PSQLTimeConverter::type(void) const
{
    return this->name;
}

std::string PSQLTimeConverter::apply(const std::string &value)
{
    return "to_timestamp(" + value + ")";
}

