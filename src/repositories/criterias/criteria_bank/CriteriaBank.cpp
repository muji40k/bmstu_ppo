#include "CriteriaBank.h"

#include <utility>

void CriteriaBank::set(std::string name, std::shared_ptr<const ICriteria> criteria)
{
    auto iter = this->bank.find(name);

    if (this->bank.end() != iter)
        (*iter).second = criteria;
    else
        this->bank.emplace(std::make_pair(name, criteria));
}

std::shared_ptr<const ICriteria> CriteriaBank::get(std::string name) const
{
    auto iter = this->bank.find(name);

    if (this->bank.end() == iter)
        throw CALL_EX(NotSetCriteriaBankException);

    return (*iter).second;
}

