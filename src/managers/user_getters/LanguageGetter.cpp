#include "LanguageGetter.h"

#include "QueryableFilterGeneric.h"

#include "typestring.h"

#include "ValueCriteria.h"
#include "HumanLanguage.h"

const std::string &LanguageGetter::type(void)
{
    return TypeName::get<HumanLanguage>();
}

void LanguageGetter::map(AppContext &context, const std::string &id, UserMapper::Map &map)
{
    auto repo = context.getRepositoryContext().getHumanLanguageRepository();

    ValueCriteria criteria (TypeName::getAttribute<HumanLanguage>("id"), "=", id);
    auto set = repo->get(criteria);

    auto id_iter = set->begin();

    if (!set->end()->notEqual(id_iter) || id_iter->get() != std::stoull(id))
        return;

    const HumanLanguage &hl = set->beginId(id_iter)->get();
    std::list<Language> languages = hl.get(AllFilter<Language>());

    for (const Language &lang : languages)
    {
        std::string lname = std::string("language_") + lang.name;
        map.emplace(std::pair<std::string, std::string>(lname, hl.getLevel(lang)));
    }
}

