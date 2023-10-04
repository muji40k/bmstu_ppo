#include "UiPlaceMapper.h"

#include <utility>

#include "typestring.h"
#include "date_common.h"

#include "GenericUiTimeChangeableIterator.h"
#include "GenericUiCriteriaParser.h"
#include "GenericExceptionWrap.h"

#include "Place.h"
#include "CRUDAdminCommand.h"
#include "RegisterCommand.h"
#include "PlaceAdminInfoStrategies.h"

static IAdminModel::Map mapFunc(const Place &country);
static Place unmap(IAdminModel::Map map);

UiPlaceMapper::UiPlaceMapper(std::shared_ptr<Facade> facade)
    : facade(facade)
{
    if (nullptr == facade)
        throw CALL_EX(NullptrAdminModelException);
}

WRAP_ADMIN_CRUD
(
    void UiPlaceMapper::create(std::string hash, IAdminModel::Map map),
    {
        Place country = unmap(map);

        PlaceCreateAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiPlaceMapper::update(std::string hash, IAdminModel::Map map),
    {
        Place country = unmap(map);

        PlaceUpdateAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiPlaceMapper::remove(std::string hash, IAdminModel::Map map),
    {
        Place country = unmap(map);

        PlaceEraseSingleAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiPlaceMapper::remove(std::string hash, std::list<IAdminModel::CriteriaMap> criterias),
    {
        std::shared_ptr<ICriteriaBuilder> builder = buildCriteria<Place>(criterias);
        PlaceEraseAdminInfoStrategy strategy (*builder->get());
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

template <>
IAdminModel::Map GenericUiTimeChangeableIterator<Place>::get(void) const
{
    return mapFunc(this->iter->get());
}

WRAP_ADMIN_CRUD
(
    IAdminModel::Set UiPlaceMapper::get(std::string hash, std::list<IAdminModel::CriteriaMap> criterias),
    {
        std::shared_ptr<ICriteriaBuilder> builder = buildCriteria<Place>(criterias);
        std::shared_ptr<PlaceGetAdminInfoStrategy> strategy = nullptr;

        if (nullptr == builder)
            strategy = std::make_shared<PlaceGetAdminInfoStrategy>();
        else
            strategy = std::make_shared<PlaceGetAdminInfoStrategy>(*builder->get());

        CRUDAdminCommand command (hash, *strategy);

        facade->run(command);

        return IAdminModel::Set(std::make_shared<GenericUiTimeChangeableSet<Place>>(strategy->result()));
    }
)

IAdminModel::Map UiPlaceMapper::getEmptyMap(void)
{
    Place empty;

    return mapFunc(empty);
}

static Place unmap(IAdminModel::Map map)
{
    Place country;

    country.id = std::stoull(map.at("id"));
    country.type = map.at("type");
    country.name = map.at("name");
    country.area = std::stod(map.at("area"));
    country.continent = map.at("continent");
    country.validFrom = DateCommon::parseTime(map.at("validFrom"),
                                              "%A %B %d %H:%M:%S %Y");

    return country;
}

static IAdminModel::Map mapFunc(const Place &country)
{
    IAdminModel::Map out;

    out.emplace(std::make_pair("id", std::to_string(*country.id)));
    out.emplace(std::make_pair("type", *country.type));
    out.emplace(std::make_pair("name", *country.name));
    out.emplace(std::make_pair("area", std::to_string(*country.area)));
    out.emplace(std::make_pair("continent", *country.continent));
    out.emplace(std::make_pair("validFrom", DateCommon::getTime(country.validFrom)));

    return out;
}

