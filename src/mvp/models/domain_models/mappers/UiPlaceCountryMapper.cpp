#include "UiPlaceCountryMapper.h"

#include <utility>

#include "typestring.h"
#include "date_common.h"

#include "GenericUiTimeChangeableIterator.h"
#include "GenericUiCriteriaParser.h"
#include "GenericExceptionWrap.h"

#include "PlaceCountry.h"
#include "CRUDAdminCommand.h"
#include "RegisterCommand.h"
#include "PlaceAdminInfoStrategies.h"

static IAdminModel::Map mapFunc(const PlaceCountry &country);
static PlaceCountry unmap(IAdminModel::Map map);

UiPlaceCountryMapper::UiPlaceCountryMapper(std::shared_ptr<Facade> facade)
    : facade(facade)
{
    if (nullptr == facade)
        throw CALL_EX(NullptrAdminModelException);
}

WRAP_ADMIN_CRUD
(
    void UiPlaceCountryMapper::create(std::string hash, IAdminModel::Map map),
    {
        PlaceCountry country = unmap(map);

        PlaceCountryCreateAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiPlaceCountryMapper::update(std::string hash, IAdminModel::Map map),
    {
        PlaceCountry country = unmap(map);

        PlaceCountryUpdateAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiPlaceCountryMapper::remove(std::string hash, IAdminModel::Map map),
    {
        PlaceCountry country = unmap(map);

        PlaceCountryEraseSingleAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiPlaceCountryMapper::remove(std::string hash, std::list<IAdminModel::CriteriaMap> criterias),
    {
        std::shared_ptr<ICriteriaBuilder> builder = buildCriteria<PlaceCountry>(criterias);
        PlaceCountryEraseAdminInfoStrategy strategy (*builder->get());
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

template <>
IAdminModel::Map GenericUiTimeChangeableIterator<PlaceCountry>::get(void) const
{
    return mapFunc(this->iter->get());
}

WRAP_ADMIN_CRUD
(
    IAdminModel::Set UiPlaceCountryMapper::get(std::string hash, std::list<IAdminModel::CriteriaMap> criterias),
    {
        std::shared_ptr<ICriteriaBuilder> builder = buildCriteria<PlaceCountry>(criterias);
        std::shared_ptr<PlaceCountryGetAdminInfoStrategy> strategy = nullptr;

        if (nullptr == builder)
            strategy = std::make_shared<PlaceCountryGetAdminInfoStrategy>();
        else
            strategy = std::make_shared<PlaceCountryGetAdminInfoStrategy>(*builder->get());

        CRUDAdminCommand command (hash, *strategy);

        facade->run(command);

        return IAdminModel::Set(std::make_shared<GenericUiTimeChangeableSet<PlaceCountry>>(strategy->result()));
    }
)

IAdminModel::Map UiPlaceCountryMapper::getEmptyMap(void)
{
    PlaceCountry empty;

    return mapFunc(empty);
}

static PlaceCountry unmap(IAdminModel::Map map)
{
    PlaceCountry place;

    Country country;
    country.id = std::stoull(map.at("country.id"));

    place.id = std::stoull(map.at("id"));
    place.country = country;
    place.validFrom = DateCommon::parseTime(map.at("validFrom"),
                                              "%A %B %d %H:%M:%S %Y");

    return place;
}

static IAdminModel::Map mapFunc(const PlaceCountry &country)
{
    IAdminModel::Map out;

    out.emplace(std::make_pair("id", std::to_string(*country.id)));
    out.emplace(std::make_pair("country.id", std::to_string(*country.country->id)));
    out.emplace(std::make_pair("validFrom", DateCommon::getTime(country.validFrom)));

    return out;
}

