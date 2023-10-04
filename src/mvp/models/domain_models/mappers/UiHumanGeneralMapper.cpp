#include "UiHumanGeneralMapper.h"

#include <utility>

#include "typestring.h"
#include "date_common.h"

#include "GenericUiTimeChangeableIterator.h"
#include "GenericUiCriteriaParser.h"
#include "GenericExceptionWrap.h"

#include "HumanGeneral.h"
#include "CRUDAdminCommand.h"
#include "RegisterCommand.h"
#include "HumanAdminInfoStrategies.h"

static IAdminModel::Map mapFunc(const HumanGeneral &country);
static HumanGeneral unmap(IAdminModel::Map map);

UiHumanGeneralMapper::UiHumanGeneralMapper(std::shared_ptr<Facade> facade)
    : facade(facade)
{
    if (nullptr == facade)
        throw CALL_EX(NullptrAdminModelException);
}

WRAP_ADMIN_CRUD
(
    void UiHumanGeneralMapper::create(std::string hash, IAdminModel::Map map),
    {
        HumanGeneral country = unmap(map);

        HumanGeneralCreateAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiHumanGeneralMapper::update(std::string hash, IAdminModel::Map map),
    {
        HumanGeneral country = unmap(map);

        HumanGeneralUpdateAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiHumanGeneralMapper::remove(std::string hash, IAdminModel::Map map),
    {
        HumanGeneral country = unmap(map);

        HumanGeneralEraseSingleAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiHumanGeneralMapper::remove(std::string hash, std::list<IAdminModel::CriteriaMap> criterias),
    {
        std::shared_ptr<ICriteriaBuilder> builder = buildCriteria<HumanGeneral>(criterias);
        HumanGeneralEraseAdminInfoStrategy strategy (*builder->get());
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

template <>
IAdminModel::Map GenericUiTimeChangeableIterator<HumanGeneral>::get(void) const
{
    return mapFunc(this->iter->get());
}

WRAP_ADMIN_CRUD
(
    IAdminModel::Set UiHumanGeneralMapper::get(std::string hash, std::list<IAdminModel::CriteriaMap> criterias),
    {
        std::shared_ptr<ICriteriaBuilder> builder = buildCriteria<HumanGeneral>(criterias);
        std::shared_ptr<HumanGeneralGetAdminInfoStrategy> strategy = nullptr;

        if (nullptr == builder)
            strategy = std::make_shared<HumanGeneralGetAdminInfoStrategy>();
        else
            strategy = std::make_shared<HumanGeneralGetAdminInfoStrategy>(*builder->get());

        CRUDAdminCommand command (hash, *strategy);

        facade->run(command);

        return IAdminModel::Set(std::make_shared<GenericUiTimeChangeableSet<HumanGeneral>>(strategy->result()));
    }
)

IAdminModel::Map UiHumanGeneralMapper::getEmptyMap(void)
{
    HumanGeneral empty;

    return mapFunc(empty);
}

static HumanGeneral unmap(IAdminModel::Map map)
{
    HumanGeneral country;

    country.id = std::stoull(map.at("id"));
    country.bloodType = map.at("bloodType");
    country.gender = map.at("gender");
    country.race = map.at("race");
    country.validFrom = DateCommon::parseTime(map.at("validFrom"),
                                              "%A %B %d %H:%M:%S %Y");

    return country;
}

static IAdminModel::Map mapFunc(const HumanGeneral &country)
{
    IAdminModel::Map out;

    out.emplace(std::make_pair("id", std::to_string(*country.id)));
    out.emplace(std::make_pair("bloodType", *country.bloodType));
    out.emplace(std::make_pair("gender", *country.gender));
    out.emplace(std::make_pair("race", *country.race));
    out.emplace(std::make_pair("validFrom", DateCommon::getTime(country.validFrom)));

    return out;
}

