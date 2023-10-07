#include "UiCountryMapper.h"

#include <utility>

#include "typestring.h"
#include "date_common.h"

#include "GenericUiTimeChangeableIterator.h"
#include "GenericUiCriteriaParser.h"
#include "GenericExceptionWrap.h"

#include "Country.h"
#include "CRUDAdminCommand.h"
#include "RegisterCommand.h"
#include "CountryAdminInfoStrategies.h"

static IAdminModel::Map mapFunc(const Country &country);
static Country unmap(IAdminModel::Map map);

UiCountryMapper::UiCountryMapper(std::shared_ptr<Facade> facade)
    : facade(facade)
{
    if (nullptr == facade)
        throw CALL_EX(NullptrAdminModelException);
}

WRAP_ADMIN_CRUD
(
    void UiCountryMapper::create(std::string hash, IAdminModel::Map map),
    {
        Country country = unmap(map);

        CountryCreateAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiCountryMapper::update(std::string hash, IAdminModel::Map map),
    {
        Country country = unmap(map);

        CountryUpdateAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiCountryMapper::remove(std::string hash, IAdminModel::Map map),
    {
        Country country = unmap(map);

        CountryEraseSingleAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiCountryMapper::remove(std::string hash, std::list<IAdminModel::CriteriaMap> criterias),
    {
        std::shared_ptr<ICriteriaBuilder> builder = buildCriteria<Country>(criterias);
        CountryEraseAdminInfoStrategy strategy (*builder->get());
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

template <>
IAdminModel::Map GenericUiTimeChangeableIterator<Country>::get(void) const
{
    return mapFunc(this->iter->get());
}

WRAP_ADMIN_CRUD
(
    IAdminModel::Set UiCountryMapper::get(std::string hash, std::list<IAdminModel::CriteriaMap> criterias),
    {
        std::shared_ptr<ICriteriaBuilder> builder = buildCriteria<Country>(criterias);
        std::shared_ptr<CountryGetAdminInfoStrategy> strategy = nullptr;

        if (nullptr == builder)
            strategy = std::make_shared<CountryGetAdminInfoStrategy>();
        else
            strategy = std::make_shared<CountryGetAdminInfoStrategy>(*builder->get());

        CRUDAdminCommand command (hash, *strategy);

        facade->run(command);

        return IAdminModel::Set(std::make_shared<GenericUiTimeChangeableSet<Country>>(strategy->result()));
    }
)

IAdminModel::Map UiCountryMapper::getEmptyMap(void)
{
    Country empty;

    return mapFunc(empty);
}

static Country unmap(IAdminModel::Map map)
{
    Country country;

    country.id = std::stoull(map.at("id"));
    country.type = map.at("type");
    country.name = map.at("name");
    country.gdp = std::stod(map.at("gdp"));
    country.validFrom = DateCommon::parseTime(map.at("validFrom"),
                                              "%A %B %d %H:%M:%S %Y");

    return country;
}

static IAdminModel::Map mapFunc(const Country &country)
{
    IAdminModel::Map out;

    out.emplace(std::make_pair("id", std::to_string(*country.id)));
    out.emplace(std::make_pair("type", *country.type));
    out.emplace(std::make_pair("name", *country.name));
    out.emplace(std::make_pair("gdp", std::to_string(*country.gdp)));
    out.emplace(std::make_pair("validFrom", DateCommon::getTime(country.validFrom)));

    return out;
}


