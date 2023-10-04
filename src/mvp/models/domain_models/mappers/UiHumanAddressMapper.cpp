#include "UiHumanAddressMapper.h"

#include <utility>

#include "typestring.h"
#include "date_common.h"

#include "GenericUiTimeChangeableIterator.h"
#include "GenericUiCriteriaParser.h"
#include "GenericExceptionWrap.h"

#include "HumanAddress.h"
#include "CRUDAdminCommand.h"
#include "RegisterCommand.h"
#include "HumanAdminInfoStrategies.h"

static IAdminModel::Map mapFunc(const HumanAddress &country);
static HumanAddress unmap(IAdminModel::Map map);

UiHumanAddressMapper::UiHumanAddressMapper(std::shared_ptr<Facade> facade)
    : facade(facade)
{
    if (nullptr == facade)
        throw CALL_EX(NullptrAdminModelException);
}

WRAP_ADMIN_CRUD
(
    void UiHumanAddressMapper::create(std::string hash, IAdminModel::Map map),
    {
        HumanAddress country = unmap(map);

        HumanAddressCreateAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiHumanAddressMapper::update(std::string hash, IAdminModel::Map map),
    {
        HumanAddress country = unmap(map);

        HumanAddressUpdateAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiHumanAddressMapper::remove(std::string hash, IAdminModel::Map map),
    {
        HumanAddress country = unmap(map);

        HumanAddressEraseSingleAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiHumanAddressMapper::remove(std::string hash, std::list<IAdminModel::CriteriaMap> criterias),
    {
        std::shared_ptr<ICriteriaBuilder> builder = buildCriteria<HumanAddress>(criterias);
        HumanAddressEraseAdminInfoStrategy strategy (*builder->get());
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

template <>
IAdminModel::Map GenericUiTimeChangeableIterator<HumanAddress>::get(void) const
{
    return mapFunc(this->iter->get());
}

WRAP_ADMIN_CRUD
(
    IAdminModel::Set UiHumanAddressMapper::get(std::string hash, std::list<IAdminModel::CriteriaMap> criterias),
    {
        std::shared_ptr<ICriteriaBuilder> builder = buildCriteria<HumanAddress>(criterias);
        std::shared_ptr<HumanAddressGetAdminInfoStrategy> strategy = nullptr;

        if (nullptr == builder)
            strategy = std::make_shared<HumanAddressGetAdminInfoStrategy>();
        else
            strategy = std::make_shared<HumanAddressGetAdminInfoStrategy>(*builder->get());

        CRUDAdminCommand command (hash, *strategy);

        facade->run(command);

        return IAdminModel::Set(std::make_shared<GenericUiTimeChangeableSet<HumanAddress>>(strategy->result()));
    }
)

IAdminModel::Map UiHumanAddressMapper::getEmptyMap(void)
{
    HumanAddress empty;

    return mapFunc(empty);
}

static HumanAddress unmap(IAdminModel::Map map)
{
    HumanAddress country;

    Place place;
    place.id = std::stoull(map.at("currentPlace.id"));

    country.id = std::stoull(map.at("id"));
    country.currentPlace = place;
    country.validFrom = DateCommon::parseTime(map.at("validFrom"),
                                              "%A %B %d %H:%M:%S %Y");

    return country;
}

static IAdminModel::Map mapFunc(const HumanAddress &country)
{
    IAdminModel::Map out;

    out.emplace(std::make_pair("id", std::to_string(*country.id)));
    out.emplace(std::make_pair("currentPlace.id", std::to_string(*country.currentPlace->id)));
    out.emplace(std::make_pair("validFrom", DateCommon::getTime(country.validFrom)));

    return out;
}


