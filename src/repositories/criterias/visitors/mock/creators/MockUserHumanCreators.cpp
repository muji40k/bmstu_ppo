#include "MockValueCriteriaMakers.hpp"

#include "UserHuman.h"

template <>
const std::unordered_map<std::string, std::shared_ptr<MockValueCriteriaMakersCreator<UserHuman>>> MockValueCriteriaCreatorSet<UserHuman>::items =
{
    {TypeName::getAttribute<UserHuman>("id"),
     std::make_shared<MockClassFieldCreator<UserHuman, unsigned long long, &UserHuman::getId>>()},
    {TypeName::getAttribute<UserHuman>("human.id"),
     std::make_shared<MockClassFieldTransitiveCreator<UserHuman, Human, unsigned long long, &UserHuman::getHuman, &Human::getId>>()}
};

