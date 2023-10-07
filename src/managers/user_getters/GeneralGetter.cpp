#include "GeneralGetter.h"

#include "typestring.h"

#include "ValueCriteria.h"
#include "HumanGeneral.h"

const std::string &GeneralGetter::type(void)
{
    return TypeName::get<HumanGeneral>();
}

void GeneralGetter::map(AppContext &context, const std::string &id, UserMapper::Map &map)
{
    auto repo = context.getRepositoryContext().getHumanGeneralRepository();

    ValueCriteria criteria (TypeName::getAttribute<HumanGeneral>("id"), "=", id);
    auto set = repo->get(criteria);

    auto id_iter = set->begin();

    if (!set->end()->notEqual(id_iter) || id_iter->get() != std::stoull(id))
        return;

    const HumanGeneral &hg = set->beginId(id_iter)->get();
    map.emplace(std::pair<std::string, std::string>("blood_type", hg.bloodType));
    map.emplace(std::pair<std::string, std::string>("gender", hg.gender));
    map.emplace(std::pair<std::string, std::string>("race", hg.race));
}
