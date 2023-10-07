#include "PlaceHumanBirthLinker.h"

#include "typestring.h"

#include "Human.h"
#include "ValueCriteria.h"

static std::shared_ptr<const ICriteria> getIdItem(const unsigned long long id)
{
    return std::make_shared<ValueCriteria>(TypeName::getAttribute<Human>("birthPlace.id"),
                                           "=",
                                           std::to_string(id));
}

PlaceHumanBirthLinker::PlaceHumanBirthLinker(void)
    : GenericLinker(getIdItem, TypeName::get<Human>())
{}

