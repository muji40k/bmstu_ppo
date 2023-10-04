#include "UiHumanLanguageMapper.h"

#include <utility>

#include "typestring.h"
#include "date_common.h"

#include "GenericUiTimeChangeableIterator.h"
#include "GenericUiCriteriaParser.h"
#include "GenericExceptionWrap.h"

#include "QueryableFilterGeneric.h"
#include "HumanLanguage.h"
#include "CRUDAdminCommand.h"
#include "RegisterCommand.h"
#include "HumanAdminInfoStrategies.h"

static IAdminModel::Map mapFunc(const HumanLanguage &country);
static HumanLanguage unmap(IAdminModel::Map map);

UiHumanLanguageMapper::UiHumanLanguageMapper(std::shared_ptr<Facade> facade)
    : facade(facade)
{
    if (nullptr == facade)
        throw CALL_EX(NullptrAdminModelException);
}

WRAP_ADMIN_CRUD
(
    void UiHumanLanguageMapper::create(std::string hash, IAdminModel::Map map),
    {
        HumanLanguage country = unmap(map);

        HumanLanguageCreateAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiHumanLanguageMapper::update(std::string hash, IAdminModel::Map map),
    {
        HumanLanguage country = unmap(map);

        HumanLanguageUpdateAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiHumanLanguageMapper::remove(std::string hash, IAdminModel::Map map),
    {
        HumanLanguage country = unmap(map);

        HumanLanguageEraseSingleAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiHumanLanguageMapper::remove(std::string hash, std::list<IAdminModel::CriteriaMap> criterias),
    {
        std::shared_ptr<ICriteriaBuilder> builder = buildCriteria<HumanLanguage>(criterias);
        HumanLanguageEraseAdminInfoStrategy strategy (*builder->get());
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

template <>
IAdminModel::Map GenericUiTimeChangeableIterator<HumanLanguage>::get(void) const
{
    return mapFunc(this->iter->get());
}

WRAP_ADMIN_CRUD
(
    IAdminModel::Set UiHumanLanguageMapper::get(std::string hash, std::list<IAdminModel::CriteriaMap> criterias),
    {
        std::shared_ptr<ICriteriaBuilder> builder = buildCriteria<HumanLanguage>(criterias);
        std::shared_ptr<HumanLanguageGetAdminInfoStrategy> strategy = nullptr;

        if (nullptr == builder)
            strategy = std::make_shared<HumanLanguageGetAdminInfoStrategy>();
        else
            strategy = std::make_shared<HumanLanguageGetAdminInfoStrategy>(*builder->get());

        CRUDAdminCommand command (hash, *strategy);

        facade->run(command);

        return IAdminModel::Set(std::make_shared<GenericUiTimeChangeableSet<HumanLanguage>>(strategy->result()));
    }
)

IAdminModel::Map UiHumanLanguageMapper::getEmptyMap(void)
{
    HumanLanguage empty;

    return mapFunc(empty);
}

static HumanLanguage unmap(IAdminModel::Map map)
{
    HumanLanguage country;

    country.id = std::stoull(map.at("id"));
    country.validFrom = DateCommon::parseTime(map.at("validFrom"),
                                              "%A %B %d %H:%M:%S %Y");

    for (auto pair : map)
        if ("id" != pair.first && "validFrom" != pair.first)
        {
            Language l;
            l.id = std::stoull(pair.first);
            country.add(l);
            country.setLevel(l, pair.second);
        }

    return country;
}

static IAdminModel::Map mapFunc(const HumanLanguage &country)
{
    IAdminModel::Map out;

    out.emplace(std::make_pair("id", std::to_string(*country.id)));
    out.emplace(std::make_pair("validFrom", DateCommon::getTime(country.validFrom)));

    for (auto lang : country.get(AllFilter<Language>()))
        out.emplace(std::make_pair(std::to_string(*lang.id), country.getLevel(lang)));

    return out;
}

