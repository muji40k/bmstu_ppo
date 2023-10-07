#include "MockValueCriteriaMakers.hpp"

#include "HumanLanguage.h"

template <>
const std::unordered_map<std::string, std::shared_ptr<MockValueCriteriaMakersCreator<HumanLanguage>>> MockValueCriteriaCreatorSet<HumanLanguage>::items =
{
    {TypeName::getAttribute<HumanLanguage>("id"),
     std::make_shared<MockClassFieldCreator<HumanLanguage, unsigned long long, &HumanLanguage::getId>>()},
    {TypeName::getAttribute<HumanLanguage>("validFrom"),
     std::make_shared<MockClassFieldCreator<HumanLanguage, std::time_t, &HumanLanguage::getTime>>()},
};

