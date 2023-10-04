#include "UiHumanMapper.h"

#include <utility>

#include "typestring.h"
#include "date_common.h"

#include "GenericUiTimeChangeableIterator.h"
#include "GenericUiCriteriaParser.h"
#include "GenericExceptionWrap.h"

#include "Human.h"
#include "CRUDAdminCommand.h"
#include "RegisterCommand.h"
#include "HumanAdminInfoStrategies.h"

static IAdminModel::Map mapFunc(const Human &country);
static Human unmap(IAdminModel::Map map);

UiHumanMapper::UiHumanMapper(std::shared_ptr<Facade> facade)
    : facade(facade)
{
    if (nullptr == facade)
        throw CALL_EX(NullptrAdminModelException);
}

WRAP_ADMIN_CRUD
(
    void UiHumanMapper::create(std::string hash, IAdminModel::Map map),
    {
        Human country = unmap(map);

        HumanCreateAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiHumanMapper::update(std::string hash, IAdminModel::Map map),
    {
        Human country = unmap(map);

        HumanUpdateAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiHumanMapper::remove(std::string hash, IAdminModel::Map map),
    {
        Human country = unmap(map);

        HumanEraseSingleAdminInfoStrategy strategy (country);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiHumanMapper::remove(std::string hash, std::list<IAdminModel::CriteriaMap> criterias),
    {
        std::shared_ptr<ICriteriaBuilder> builder = buildCriteria<Human>(criterias);
        HumanEraseAdminInfoStrategy strategy (*builder->get());
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

template <>
IAdminModel::Map GenericUiTimeChangeableIterator<Human>::get(void) const
{
    return mapFunc(this->iter->get());
}

WRAP_ADMIN_CRUD
(
    IAdminModel::Set UiHumanMapper::get(std::string hash, std::list<IAdminModel::CriteriaMap> criterias),
    {
        std::shared_ptr<ICriteriaBuilder> builder = buildCriteria<Human>(criterias);
        std::shared_ptr<HumanGetAdminInfoStrategy> strategy = nullptr;

        if (nullptr == builder)
            strategy = std::make_shared<HumanGetAdminInfoStrategy>();
        else
            strategy = std::make_shared<HumanGetAdminInfoStrategy>(*builder->get());

        CRUDAdminCommand command (hash, *strategy);

        facade->run(command);

        return IAdminModel::Set(std::make_shared<GenericUiTimeChangeableSet<Human>>(strategy->result()));
    }
)

IAdminModel::Map UiHumanMapper::getEmptyMap(void)
{
    Human empty;
    empty.setIsPatronymic(true);

    return mapFunc(empty);
}

static Human unmap(IAdminModel::Map map)
{
    Human country;

    Place place;
    place.id = std::stoull(map.at("birthPlace.id"));

    country.id = std::stoull(map.at("id"));
    country.firstName = map.at("firstName");
    country.lastName = map.at("lastName");
    country.birthPlace = place;

    if ("" != map.at("patronymic"))
    {
        country.setIsPatronymic(true);
        country.patronymic = map.at("patronymic");
    }

    country.validFrom = DateCommon::parseTime(map.at("validFrom"),
                                              "%A %B %d %H:%M:%S %Y");

    return country;
}

static IAdminModel::Map mapFunc(const Human &country)
{
    IAdminModel::Map out;

    out.emplace(std::make_pair("id", std::to_string(*country.id)));
    out.emplace(std::make_pair("firstName", *country.firstName));
    out.emplace(std::make_pair("lastName", *country.lastName));

    if (country.isPatronymic())
        out.emplace(std::make_pair("patronymic", *country.patronymic));
    else
        out.emplace(std::make_pair("patronymic", ""));

    out.emplace(std::make_pair("birthPlace.id", std::to_string(*country.birthPlace->id)));
    out.emplace(std::make_pair("validFrom", DateCommon::getTime(country.validFrom)));

    return out;
}


