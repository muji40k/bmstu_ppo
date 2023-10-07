#include "MockValueCriteriaMakers.hpp"

#include "HumanSocial.h"

template <>
const std::unordered_map<std::string, std::shared_ptr<MockValueCriteriaMakersCreator<HumanSocial>>> MockValueCriteriaCreatorSet<HumanSocial>::items =
{
    {TypeName::getAttribute<HumanSocial>("id"),
     std::make_shared<MockClassFieldCreator<HumanSocial, unsigned long long, &HumanSocial::getId>>()},
    {TypeName::getAttribute<HumanSocial>("religion"),
     std::make_shared<MockClassFieldCreator<HumanSocial, std::string, &HumanSocial::getReligion>>()},
    {TypeName::getAttribute<HumanSocial>("wealth"),
     std::make_shared<MockClassFieldCreator<HumanSocial, std::string, &HumanSocial::getWealth>>()},
    {TypeName::getAttribute<HumanSocial>("literacy"),
     std::make_shared<MockClassFieldCreator<HumanSocial, std::string, &HumanSocial::getLiteracy>>()},
    {TypeName::getAttribute<HumanSocial>("busyness"),
     std::make_shared<MockClassFieldCreator<HumanSocial, std::string, &HumanSocial::getBusyness>>()},
    {TypeName::getAttribute<HumanSocial>("validFrom"),
     std::make_shared<MockClassFieldCreator<HumanSocial, std::time_t, &HumanSocial::getTime>>()}
};

