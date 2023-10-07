#include "MockValueCriteriaMakers.hpp"

#include "HumanGeneral.h"

template <>
const std::unordered_map<std::string, std::shared_ptr<MockValueCriteriaMakersCreator<HumanGeneral>>> MockValueCriteriaCreatorSet<HumanGeneral>::items =
{
    {TypeName::getAttribute<HumanGeneral>("id"),
     std::make_shared<MockClassFieldCreator<HumanGeneral, unsigned long long, &HumanGeneral::getId>>()},
    {TypeName::getAttribute<HumanGeneral>("bloodType"),
     std::make_shared<MockClassFieldCreator<HumanGeneral, std::string, &HumanGeneral::getBloodType>>()},
    {TypeName::getAttribute<HumanGeneral>("gender"),
     std::make_shared<MockClassFieldCreator<HumanGeneral, std::string, &HumanGeneral::getGender>>()},
    {TypeName::getAttribute<HumanGeneral>("race"),
     std::make_shared<MockClassFieldCreator<HumanGeneral, std::string, &HumanGeneral::getRace>>()},
    {TypeName::getAttribute<HumanGeneral>("validFrom"),
     std::make_shared<MockClassFieldCreator<HumanGeneral, std::time_t, &HumanGeneral::getTime>>()}
};

