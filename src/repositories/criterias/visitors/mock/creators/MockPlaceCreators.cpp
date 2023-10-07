#include "MockValueCriteriaMakers.hpp"

#include "Place.h"

template <>
const std::unordered_map<std::string, std::shared_ptr<MockValueCriteriaMakersCreator<Place>>> MockValueCriteriaCreatorSet<Place>::items =
{
    {TypeName::getAttribute<Place>("id"),
     std::make_shared<MockClassFieldCreator<Place, unsigned long long, &Place::getId>>()},
    {TypeName::getAttribute<Place>("type"),
     std::make_shared<MockClassFieldCreator<Place, std::string, &Place::getType>>()},
    {TypeName::getAttribute<Place>("name"),
     std::make_shared<MockClassFieldCreator<Place, std::string, &Place::getName>>()},
    {TypeName::getAttribute<Place>("area"),
     std::make_shared<MockClassFieldCreator<Place, double, &Place::getArea>>()},
    {TypeName::getAttribute<Place>("continent"),
     std::make_shared<MockClassFieldCreator<Place, std::string, &Place::getContinent>>()},
    {TypeName::getAttribute<Place>("validFrom"),
     std::make_shared<MockClassFieldCreator<Place, std::time_t, &Place::getTime>>()}
};

