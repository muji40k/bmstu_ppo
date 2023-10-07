#include "UiUserMapper.h"

#include <utility>

#include "typestring.h"

#include "GenericUiIterator.h"
#include "GenericUiCriteriaParser.h"
#include "GenericExceptionWrap.h"

#include "User.h"
#include "CRUDAdminCommand.h"
#include "RegisterCommand.h"
#include "UserAdminInfoStrategies.h"

static IAdminModel::Map mapFunc(const User &user);
static User unmap(IAdminModel::Map map);

UiUserMapper::UiUserMapper(std::shared_ptr<Facade> facade)
    : facade(facade)
{
    if (nullptr == facade)
        throw CALL_EX(NullptrAdminModelException);
}

WRAP_ADMIN_CRUD
(
    void UiUserMapper::create(std::string, IAdminModel::Map map),
    {
        User user = unmap(map);
        RegisterCommand command (user.name, user.email, user.password);
        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiUserMapper::update(std::string hash, IAdminModel::Map map),
    {
        User user = unmap(map);

        UserUpdateAdminInfoStrategy strategy (user);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiUserMapper::remove(std::string hash, IAdminModel::Map map),
    {
        User user = unmap(map);

        UserEraseSingleAdminInfoStrategy strategy (user);
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

WRAP_ADMIN_CRUD
(
    void UiUserMapper::remove(std::string hash, std::list<IAdminModel::CriteriaMap> criterias),
    {
        std::shared_ptr<ICriteriaBuilder> builder = buildCriteria<User>(criterias);
        UserEraseAdminInfoStrategy strategy (*builder->get());
        CRUDAdminCommand command (hash, strategy);

        facade->run(command);
    }
)

template <>
IAdminModel::Map GenericUiIterator<User>::get(void) const
{
    return mapFunc(this->iter->get());
}

WRAP_ADMIN_CRUD
(
    IAdminModel::Set UiUserMapper::get(std::string hash, std::list<IAdminModel::CriteriaMap> criterias),
    {
        std::shared_ptr<ICriteriaBuilder> builder = buildCriteria<User>(criterias);
        std::shared_ptr<UserGetAdminInfoStrategy> strategy = nullptr;

        if (nullptr == builder)
            strategy = std::make_shared<UserGetAdminInfoStrategy>();
        else
            strategy = std::make_shared<UserGetAdminInfoStrategy>(*builder->get());

        CRUDAdminCommand command (hash, *strategy);

        facade->run(command);

        return IAdminModel::Set(std::make_shared<GenericUiSet<User>>(strategy->result()));
    }
)

IAdminModel::Map UiUserMapper::getEmptyMap(void)
{
    User empty;

    return mapFunc(empty);
}

static User unmap(IAdminModel::Map map)
{
    User user;

    user.id = std::stoull(map.at("id"));
    user.email = map.at("email");
    user.password = map.at("password");
    user.name = map.at("name");

    return user;
}

static IAdminModel::Map mapFunc(const User &user)
{
    IAdminModel::Map out;

    out.emplace(std::make_pair("id", std::to_string(user.id)));
    out.emplace(std::make_pair("email", *user.email));
    out.emplace(std::make_pair("name", *user.name));
    out.emplace(std::make_pair("password", *user.password));

    return out;
}

