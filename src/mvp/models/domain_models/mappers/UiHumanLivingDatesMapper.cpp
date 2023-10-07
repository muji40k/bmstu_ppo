#include "UiHumanLivingDatesMapper.h"

#include <utility>

#include "typestring.h"
#include "date_common.h"

#include "GenericUiTimeChangeableIterator.h"
#include "GenericUiCriteriaParser.h"
#include "GenericExceptionWrap.h"

#include "HumanLivingDates.h"
#include "CRUDAdminCommand.h"
#include "RegisterCommand.h"
#include "HumanAdminInfoStrategies.h"

static IAdminModel::Map mapFunc(const HumanLivingDates &country);
static HumanLivingDates unmap(IAdminModel::Map map);

UiHumanLivingDatesMapper::UiHumanLivingDatesMapper(std::shared_ptr<Facade> facade)
    : facade(facade)
{
    if (nullptr == facade)
        throw CALL_EX(NullptrAdminModelException);
}

WRAP_ADMIN_CRUD
(
    void UiHumanLivingDatesMapper::create(std::string hash, IAdminModel::Map map),
    {
        HumanLivingDates country = unmap(map);

        HumanLivingDatesCreateAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiHumanLivingDatesMapper::update(std::string hash, IAdminModel::Map map),
    {
        HumanLivingDates country = unmap(map);

        HumanLivingDatesUpdateAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiHumanLivingDatesMapper::remove(std::string hash, IAdminModel::Map map),
    {
        HumanLivingDates country = unmap(map);

        HumanLivingDatesEraseSingleAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiHumanLivingDatesMapper::remove(std::string hash, std::list<IAdminModel::CriteriaMap> criterias),
    {
        std::shared_ptr<ICriteriaBuilder> builder = buildCriteria<HumanLivingDates>(criterias);
        HumanLivingDatesEraseAdminInfoStrategy strategy (*builder->get());
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

template <>
IAdminModel::Map GenericUiTimeChangeableIterator<HumanLivingDates>::get(void) const
{
    return mapFunc(this->iter->get());
}

WRAP_ADMIN_CRUD
(
    IAdminModel::Set UiHumanLivingDatesMapper::get(std::string hash, std::list<IAdminModel::CriteriaMap> criterias),
    {
        std::shared_ptr<ICriteriaBuilder> builder = buildCriteria<HumanLivingDates>(criterias);
        std::shared_ptr<HumanLivingDatesGetAdminInfoStrategy> strategy = nullptr;

        if (nullptr == builder)
            strategy = std::make_shared<HumanLivingDatesGetAdminInfoStrategy>();
        else
            strategy = std::make_shared<HumanLivingDatesGetAdminInfoStrategy>(*builder->get());

        CRUDAdminCommand command (hash, *strategy);

        facade->run(command);

        return IAdminModel::Set(std::make_shared<GenericUiTimeChangeableSet<HumanLivingDates>>(strategy->result()));
    }
)

IAdminModel::Map UiHumanLivingDatesMapper::getEmptyMap(void)
{
    HumanLivingDates empty;

    return mapFunc(empty);
}

static HumanLivingDates unmap(IAdminModel::Map map)
{
    HumanLivingDates country;

    country.id = std::stoull(map.at("id"));
    country.birthDate = DateCommon::parseTime(map.at("birthDate"),
                                              "%A %B %d %H:%M:%S %Y");

    if ("" != map.at("deathDate"))
        country.deathDate = DateCommon::parseTime(map.at("deathDate"),
                                                  "%A %B %d %H:%M:%S %Y");

    country.validFrom = DateCommon::parseTime(map.at("validFrom"),
                                              "%A %B %d %H:%M:%S %Y");

    return country;
}

static IAdminModel::Map mapFunc(const HumanLivingDates &country)
{
    IAdminModel::Map out;

    out.emplace(std::make_pair("id", std::to_string(*country.id)));
    out.emplace(std::make_pair("birthDate", DateCommon::getTime(*country.birthDate)));

    if (!country.isAlive(std::time(nullptr)))
        out.emplace(std::make_pair("deathDate", DateCommon::getTime(*country.deathDate)));
    else
        out.emplace(std::make_pair("deathDate", ""));

    out.emplace(std::make_pair("validFrom", DateCommon::getTime(country.validFrom)));

    return out;
}

