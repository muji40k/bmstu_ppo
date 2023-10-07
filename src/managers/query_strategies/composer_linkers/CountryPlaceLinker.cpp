#include "CountryPlaceLinker.h"

#include "typestring.h"

#include "PlaceCountry.h"
#include "ValueCriteria.h"

static std::shared_ptr<const ICriteria> getIdItem(const unsigned long long id)
{
    return std::make_shared<ValueCriteria>(TypeName::getAttribute<PlaceCountry>("country.id"),
                                           "=",
                                           std::to_string(id));
}

CountryPlaceLinker::CountryPlaceLinker(void)
    : GenericLinker(getIdItem, TypeName::get<PlaceCountry>())
{}

