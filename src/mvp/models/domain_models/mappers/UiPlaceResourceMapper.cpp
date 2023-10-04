#include "UiPlaceResourceMapper.h"

#include <utility>

#include "typestring.h"
#include "date_common.h"

#include "GenericUiTimeChangeableIterator.h"
#include "GenericUiCriteriaParser.h"
#include "GenericExceptionWrap.h"

#include "QueryableFilterGeneric.h"
#include "PlaceResource.h"
#include "CRUDAdminCommand.h"
#include "RegisterCommand.h"
#include "PlaceAdminInfoStrategies.h"

static IAdminModel::Map mapFunc(const PlaceResource &country);
static PlaceResource unmap(IAdminModel::Map map);

UiPlaceResourceMapper::UiPlaceResourceMapper(std::shared_ptr<Facade> facade)
    : facade(facade)
{
    if (nullptr == facade)
        throw CALL_EX(NullptrAdminModelException);
}

WRAP_ADMIN_CRUD
(
    void UiPlaceResourceMapper::create(std::string hash, IAdminModel::Map map),
    {
        PlaceResource country = unmap(map);

        PlaceResourceCreateAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiPlaceResourceMapper::update(std::string hash, IAdminModel::Map map),
    {
        PlaceResource country = unmap(map);

        PlaceResourceUpdateAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiPlaceResourceMapper::remove(std::string hash, IAdminModel::Map map),
    {
        PlaceResource country = unmap(map);

        PlaceResourceEraseSingleAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiPlaceResourceMapper::remove(std::string hash, std::list<IAdminModel::CriteriaMap> criterias),
    {
        std::shared_ptr<ICriteriaBuilder> builder = buildCriteria<PlaceResource>(criterias);
        PlaceResourceEraseAdminInfoStrategy strategy (*builder->get());
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

template <>
IAdminModel::Map GenericUiTimeChangeableIterator<PlaceResource>::get(void) const
{
    return mapFunc(this->iter->get());
}

WRAP_ADMIN_CRUD
(
    IAdminModel::Set UiPlaceResourceMapper::get(std::string hash, std::list<IAdminModel::CriteriaMap> criterias),
    {
        std::shared_ptr<ICriteriaBuilder> builder = buildCriteria<PlaceResource>(criterias);
        std::shared_ptr<PlaceResourceGetAdminInfoStrategy> strategy = nullptr;

        if (nullptr == builder)
            strategy = std::make_shared<PlaceResourceGetAdminInfoStrategy>();
        else
            strategy = std::make_shared<PlaceResourceGetAdminInfoStrategy>(*builder->get());

        CRUDAdminCommand command (hash, *strategy);

        facade->run(command);

        return IAdminModel::Set(std::make_shared<GenericUiTimeChangeableSet<PlaceResource>>(strategy->result()));
    }
)

IAdminModel::Map UiPlaceResourceMapper::getEmptyMap(void)
{
    PlaceResource empty;

    return mapFunc(empty);
}

static PlaceResource unmap(IAdminModel::Map map)
{
    PlaceResource country;

    country.id = std::stoull(map.at("id"));
    country.validFrom = DateCommon::parseTime(map.at("validFrom"),
                                              "%A %B %d %H:%M:%S %Y");

    for (auto pair : map)
        if ("id" != pair.first && "validFrom" != pair.first)
        {
            Resource l;
            l.id = std::stoull(pair.first);
            country.add(l);
            country.setVolume(l, std::stod(pair.second));
        }

    return country;
}

static IAdminModel::Map mapFunc(const PlaceResource &country)
{
    IAdminModel::Map out;

    out.emplace(std::make_pair("id", std::to_string(*country.id)));
    out.emplace(std::make_pair("validFrom", DateCommon::getTime(country.validFrom)));

    for (auto lang : country.get(AllFilter<Resource>()))
        out.emplace(std::make_pair(std::to_string(*lang.id), std::to_string(country.getVolume(lang))));

    return out;
}

