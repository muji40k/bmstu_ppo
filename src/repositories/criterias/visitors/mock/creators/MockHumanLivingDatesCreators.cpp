#include "MockValueCriteriaMakers.hpp"

#include "HumanLivingDates.h"

template <>
const std::unordered_map<std::string, std::shared_ptr<MockValueCriteriaMakersCreator<HumanLivingDates>>> MockValueCriteriaCreatorSet<HumanLivingDates>::items =
{
    {TypeName::getAttribute<HumanLivingDates>("id"),
     std::make_shared<MockClassFieldCreator<HumanLivingDates, unsigned long long, &HumanLivingDates::getId>>()},
    {TypeName::getAttribute<HumanLivingDates>("birthDate"),
     std::make_shared<MockClassFieldCreator<HumanLivingDates, std::time_t, &HumanLivingDates::getBirthDate>>()},
    {TypeName::getAttribute<HumanLivingDates>("deathDate"),
     std::make_shared<MockClassFieldCreator<HumanLivingDates, std::time_t, &HumanLivingDates::getDeathDate>>()},
    {TypeName::getAttribute<HumanLivingDates>("validFrom"),
     std::make_shared<MockClassFieldCreator<HumanLivingDates, std::time_t, &HumanLivingDates::getTime>>()}
};

