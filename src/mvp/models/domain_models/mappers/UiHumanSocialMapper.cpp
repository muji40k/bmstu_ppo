#include "UiHumanSocialMapper.h"

#include <utility>

#include "typestring.h"
#include "date_common.h"

#include "GenericUiTimeChangeableIterator.h"
#include "GenericUiCriteriaParser.h"
#include "GenericExceptionWrap.h"

#include "HumanSocial.h"
#include "CRUDAdminCommand.h"
#include "RegisterCommand.h"
#include "HumanAdminInfoStrategies.h"

static IAdminModel::Map mapFunc(const HumanSocial &country);
static HumanSocial unmap(IAdminModel::Map map);

UiHumanSocialMapper::UiHumanSocialMapper(std::shared_ptr<Facade> facade)
    : facade(facade)
{
    if (nullptr == facade)
        throw CALL_EX(NullptrAdminModelException);
}

WRAP_ADMIN_CRUD
(
    void UiHumanSocialMapper::create(std::string hash, IAdminModel::Map map),
    {
        HumanSocial country = unmap(map);

        HumanSocialCreateAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiHumanSocialMapper::update(std::string hash, IAdminModel::Map map),
    {
        HumanSocial country = unmap(map);

        HumanSocialUpdateAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiHumanSocialMapper::remove(std::string hash, IAdminModel::Map map),
    {
        HumanSocial country = unmap(map);

        HumanSocialEraseSingleAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiHumanSocialMapper::remove(std::string hash, std::list<IAdminModel::CriteriaMap> criterias),
    {
        std::shared_ptr<ICriteriaBuilder> builder = buildCriteria<HumanSocial>(criterias);
        HumanSocialEraseAdminInfoStrategy strategy (*builder->get());
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

template <>
IAdminModel::Map GenericUiTimeChangeableIterator<HumanSocial>::get(void) const
{
    return mapFunc(this->iter->get());
}

WRAP_ADMIN_CRUD
(
    IAdminModel::Set UiHumanSocialMapper::get(std::string hash, std::list<IAdminModel::CriteriaMap> criterias),
    {
        std::shared_ptr<ICriteriaBuilder> builder = buildCriteria<HumanSocial>(criterias);
        std::shared_ptr<HumanSocialGetAdminInfoStrategy> strategy = nullptr;

        if (nullptr == builder)
            strategy = std::make_shared<HumanSocialGetAdminInfoStrategy>();
        else
            strategy = std::make_shared<HumanSocialGetAdminInfoStrategy>(*builder->get());

        CRUDAdminCommand command (hash, *strategy);

        facade->run(command);

        return IAdminModel::Set(std::make_shared<GenericUiTimeChangeableSet<HumanSocial>>(strategy->result()));
    }
)

IAdminModel::Map UiHumanSocialMapper::getEmptyMap(void)
{
    HumanSocial empty;

    return mapFunc(empty);
}

static HumanSocial unmap(IAdminModel::Map map)
{
    HumanSocial country;

    country.id = std::stoull(map.at("id"));
    country.religion = map.at("religion");
    country.wealth = map.at("wealth");
    country.literacy = map.at("literacy");
    country.busyness = map.at("busyness");
    country.validFrom = DateCommon::parseTime(map.at("validFrom"),
                                              "%A %B %d %H:%M:%S %Y");

    return country;
}

static IAdminModel::Map mapFunc(const HumanSocial &country)
{
    IAdminModel::Map out;

    out.emplace(std::make_pair("id", std::to_string(*country.id)));
    out.emplace(std::make_pair("religion", *country.religion));
    out.emplace(std::make_pair("wealth", *country.wealth));
    out.emplace(std::make_pair("literacy", *country.literacy));
    out.emplace(std::make_pair("busyness", *country.busyness));
    out.emplace(std::make_pair("validFrom", DateCommon::getTime(country.validFrom)));

    return out;
}


