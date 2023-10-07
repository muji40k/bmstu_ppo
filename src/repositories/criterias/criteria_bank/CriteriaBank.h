#ifndef _CRITERIABANK_H_
#define _CRITERIABANK_H_

#include <memory>
#include <unordered_map>
#include <string>

#include "repository_exceptions.h"

#include "ICriteria.h"

class CriteriaBank
{
    public:
        void set(std::string name, std::shared_ptr<const ICriteria> criteria);
        std::shared_ptr<const ICriteria> get(std::string name) const;

    private:
        std::unordered_map<std::string, std::shared_ptr<const ICriteria>> bank;
};

DEF_EX(CommonCriteriaBankException, RepositoryException,
       "Common CriteriaBank exception");
DEF_EX(NotSetCriteriaBankException, CommonCriteriaBankException,
       "Criteria for Type not set");

#endif

