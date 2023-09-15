#include "MockValueCriteriaMakers.hpp"

#include "PlaceResource.h"

template <>
const std::unordered_map<std::string, std::shared_ptr<MockValueCriteriaMakersCreator<PlaceResource>>> MockValueCriteriaCreatorSet<PlaceResource>::items =
{
    {TypeName::getAttribute<PlaceResource>("id"),
     std::make_shared<MockClassFieldCreator<PlaceResource, unsigned long long, &PlaceResource::getId>>()},
    {TypeName::getAttribute<PlaceResource>("validFrom"),
     std::make_shared<MockClassFieldCreator<PlaceResource, std::time_t, &PlaceResource::getTime>>()}
};

