#include "SocialGetter.h"

#include "typestring.h"

#include "ValueCriteria.h"
#include "HumanSocial.h"

const std::string &SocialGetter::type(void)
{
    return TypeName::get<HumanSocial>();
}

void SocialGetter::map(AppContext &context, const std::string &id, UserMapper::Map &map)
{
    auto repo = context.getRepositoryContext().getHumanSocialRepository();

    ValueCriteria criteria (TypeName::getAttribute<HumanSocial>("id"), "=", id);
    auto set = repo->get(criteria);

    auto id_iter = set->begin();

    if (!set->end()->notEqual(id_iter) || id_iter->get() != std::stoull(id))
        return;

    const HumanSocial &hs = set->beginId(id_iter)->get();
    map.emplace(std::pair<std::string, std::string>("religion", hs.religion));
    map.emplace(std::pair<std::string, std::string>("wealth", hs.wealth));
    map.emplace(std::pair<std::string, std::string>("literacy", hs.literacy));
    map.emplace(std::pair<std::string, std::string>("busyness", hs.busyness));
}

