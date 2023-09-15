#include "MockValueCriteriaMakers.hpp"

#include "PlaceCountry.h"

template <>
const std::unordered_map<std::string, std::shared_ptr<MockValueCriteriaMakersCreator<PlaceCountry>>> MockValueCriteriaCreatorSet<PlaceCountry>::items =
{
    {TypeName::getAttribute<PlaceCountry>("id"),
     std::make_shared<MockClassFieldCreator<PlaceCountry, unsigned long long, &PlaceCountry::getId>>()},
    {TypeName::getAttribute<PlaceCountry>("country.id"),
     std::make_shared<MockClassFieldTransitiveCreator<PlaceCountry, Country, unsigned long long, &PlaceCountry::getCountry, &Country::getId>>()},
    {TypeName::getAttribute<PlaceCountry>("validFrom"),
     std::make_shared<MockClassFieldCreator<PlaceCountry, std::time_t, &PlaceCountry::getTime>>()}
};

