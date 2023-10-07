#include "MockValueCriteriaMakers.hpp"

#include "Resource.h"

template <>
const std::unordered_map<std::string, std::shared_ptr<MockValueCriteriaMakersCreator<Resource>>> MockValueCriteriaCreatorSet<Resource>::items =
{
    {TypeName::getAttribute<Resource>("id"),
     std::make_shared<MockClassFieldCreator<Resource, unsigned long long, &Resource::getId>>()},
    {TypeName::getAttribute<Resource>("type"),
     std::make_shared<MockClassFieldCreator<Resource, std::string, &Resource::getType>>()},
    {TypeName::getAttribute<Resource>("name"),
     std::make_shared<MockClassFieldCreator<Resource, std::string, &Resource::getName>>()},
    {TypeName::getAttribute<Resource>("value"),
     std::make_shared<MockClassFieldCreator<Resource, double, &Resource::getValue>>()},
    {TypeName::getAttribute<Resource>("rarity"),
     std::make_shared<MockClassFieldCreator<Resource, std::string, &Resource::getRarity>>()},
    {TypeName::getAttribute<Resource>("validFrom"),
     std::make_shared<MockClassFieldCreator<Resource, std::time_t, &Resource::getTime>>()}
};

