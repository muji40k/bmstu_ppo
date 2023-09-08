#include "PlaceHumanAddressLinker.h"

#include "typestring.h"

#include "HumanAddress.h"
#include "ValueCriteria.h"

static std::shared_ptr<const ICriteria> getIdItem(const unsigned long long id)
{
    return std::make_shared<ValueCriteria>(TypeName::getAttribute<HumanAddress>("currentPlace.id"),
                                           "=",
                                           std::to_string(id));
}

PlaceHumanAddressLinker::PlaceHumanAddressLinker(void)
    : GenericLinker(getIdItem, TypeName::get<HumanAddress>())
{}

