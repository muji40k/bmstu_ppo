#include "MockValueCriteriaMakers.hpp"

#include "Country.h"

template <>
const std::unordered_map<std::string, std::shared_ptr<MockValueCriteriaMakersCreator<Country>>> MockValueCriteriaCreatorSet<Country>::items =
{
    {TypeName::getAttribute<Country>("id"),
     std::make_shared<MockClassFieldCreator<Country, unsigned long long, &Country::getId>>()},
    {TypeName::getAttribute<Country>("type"),
     std::make_shared<MockClassFieldCreator<Country, std::string, &Country::getType>>()},
    {TypeName::getAttribute<Country>("name"),
     std::make_shared<MockClassFieldCreator<Country, std::string, &Country::getName>>()},
    {TypeName::getAttribute<Country>("gdp"),
     std::make_shared<MockClassFieldCreator<Country, double, &Country::getGDP>>()},
    {TypeName::getAttribute<Country>("validFrom"),
     std::make_shared<MockClassFieldCreator<Country, std::time_t, &Country::getTime>>()}
};

