#include "MockValueCriteriaMakers.hpp"

#include "Human.h"

template <>
const std::unordered_map<std::string, std::shared_ptr<MockValueCriteriaMakersCreator<Human>>> MockValueCriteriaCreatorSet<Human>::items =
{
    {TypeName::getAttribute<Human>("id"),
     std::make_shared<MockClassFieldCreator<Human, unsigned long long, &Human::getId>>()},
    {TypeName::getAttribute<Human>("firstName"),
     std::make_shared<MockClassFieldCreator<Human, std::string, &Human::getFirstName>>()},
    {TypeName::getAttribute<Human>("lastName"),
     std::make_shared<MockClassFieldCreator<Human, std::string, &Human::getLastName>>()},
    {TypeName::getAttribute<Human>("patronymic"),
     std::make_shared<MockClassFieldCreator<Human, std::string, &Human::getPatronymic>>()},
    {TypeName::getAttribute<Human>("birthPlace.id"),
     std::make_shared<MockClassFieldTransitiveCreator<Human, Place, unsigned long long, &Human::getBirthPlace, &Place::getId>>()},
    {TypeName::getAttribute<Human>("validFrom"),
     std::make_shared<MockClassFieldCreator<Human, std::time_t, &Human::getTime>>()},

};

