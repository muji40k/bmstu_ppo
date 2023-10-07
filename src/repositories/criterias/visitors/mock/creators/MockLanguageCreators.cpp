#include "MockValueCriteriaMakers.hpp"

#include "Language.h"

template <>
const std::unordered_map<std::string, std::shared_ptr<MockValueCriteriaMakersCreator<Language>>> MockValueCriteriaCreatorSet<Language>::items =
{
    {TypeName::getAttribute<Language>("id"),
     std::make_shared<MockClassFieldCreator<Language, unsigned long long, &Language::getId>>()},
    {TypeName::getAttribute<Language>("name"),
     std::make_shared<MockClassFieldCreator<Language, std::string, &Language::getName>>()},
    {TypeName::getAttribute<Language>("family"),
     std::make_shared<MockClassFieldCreator<Language, std::string, &Language::getFamily>>()},
    {TypeName::getAttribute<Language>("validFrom"),
     std::make_shared<MockClassFieldCreator<Language, std::time_t, &Language::getTime>>()}
};

