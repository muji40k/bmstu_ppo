#include "LivingDatesGetter.h"

#include "typestring.h"

#include "ValueCriteria.h"
#include "HumanLivingDates.h"

const std::string &LivingDatesGetter::type(void)
{
    return TypeName::get<HumanLivingDates>();
}

void LivingDatesGetter::map(AppContext &context, const std::string &id, UserMapper::Map &map)
{
    auto repo = context.getRepositoryContext().getHumanLivingDatesRepository();

    ValueCriteria criteria (TypeName::getAttribute<HumanLivingDates>("id"), "=", id);
    auto set = repo->get(criteria);

    auto id_iter = set->begin();

    if (!set->end()->notEqual(id_iter) || id_iter->get() != std::stoull(id))
        return;

    const HumanLivingDates &hld = set->beginId(id_iter)->get();
    map.emplace(std::pair<std::string, std::string>("birth_date", std::to_string(hld.birthDate)));

    std::time_t now = std::time(nullptr);

    if (hld.isAlive(now))
        map.emplace(std::pair<std::string, std::string>("age", std::to_string(hld.getAge(now))));
    else
        map.emplace(std::pair<std::string, std::string>("death_date", std::to_string(hld.deathDate)));
}

