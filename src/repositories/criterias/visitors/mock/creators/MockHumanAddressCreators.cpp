#include "MockValueCriteriaMakers.hpp"

#include "HumanAddress.h"

template <>
const std::unordered_map<std::string, std::shared_ptr<MockValueCriteriaMakersCreator<HumanAddress>>> MockValueCriteriaCreatorSet<HumanAddress>::items =
{
    {TypeName::getAttribute<HumanAddress>("id"),
     std::make_shared<MockClassFieldCreator<HumanAddress, unsigned long long, &HumanAddress::getId>>()},
    {TypeName::getAttribute<HumanAddress>("currentPlace.id"),
     std::make_shared<MockClassFieldTransitiveCreator<HumanAddress, Place, unsigned long long, &HumanAddress::getCurrentPlace, &Place::getId>>()},
    {TypeName::getAttribute<HumanAddress>("validFrom"),
     std::make_shared<MockClassFieldCreator<HumanAddress, std::time_t, &HumanAddress::getTime>>()},

};

