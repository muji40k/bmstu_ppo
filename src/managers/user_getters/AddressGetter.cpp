#include "AddressGetter.h"

#include "typestring.h"

#include "ValueCriteria.h"
#include "HumanAddress.h"

const std::string &AddressGetter::type(void)
{
    return TypeName::get<HumanAddress>();
}

void AddressGetter::map(AppContext &context, const std::string &id, UserMapper::Map &map)
{
    auto repo = context.getRepositoryContext().getHumanAddressRepository();

    ValueCriteria criteria (TypeName::getAttribute<HumanAddress>("id"), "=", id);
    auto set = repo->get(criteria);

    auto id_iter = set->begin();

    if (!set->end()->notEqual(id_iter) || id_iter->get() != std::stoull(id))
        return;

    const HumanAddress &ha = set->beginId(id_iter)->get();
    map.emplace(std::pair<std::string, std::string>("address", ha.currentPlace->name));
}

