#include "CriteriaFieldMapper.h"

#include <utility>

CriteriaFieldMapper::CriteriaFieldMapper(const std::unordered_map<std::string, std::string> &map)
    : map(map)
{}

const std::string &CriteriaFieldMapper::get(std::string key) const
{
    auto iter = this->map.find(key);

    if (this->map.end() == iter)
        throw CALL_EX(NotSetCriteriaFieldMapperException);

    return (*iter).second;
}

void CriteriaFieldMapper::set(std::string key, std::string value)
{
    auto iter = this->map.find(key);

    if (this->map.end() == iter)
        this->map.emplace(std::make_pair(key, value));
    else
        (*iter).second = value;
}

