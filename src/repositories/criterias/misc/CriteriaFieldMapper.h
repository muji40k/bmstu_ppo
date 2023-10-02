#ifndef _CRITERIAFIELDMAPPER_H_
#define _CRITERIAFIELDMAPPER_H_

#include <string>
#include <unordered_map>

#include "repository_exceptions.h"

class CriteriaFieldMapper
{
    public:
        CriteriaFieldMapper(void) = default;
        CriteriaFieldMapper(const std::unordered_map<std::string, std::string> &map);

        const std::string &get(std::string key) const;
        void set(std::string key, std::string value);

    private:
        std::unordered_map<std::string, std::string> map;
};

DEF_EX(CommonCriteriaFieldMapperException, RepositoryException,
       "Common CriteriaFieldMapper exception");
DEF_EX(NotSetCriteriaFieldMapperException, CommonCriteriaFieldMapperException,
       "Value for key isn't set");

#endif

