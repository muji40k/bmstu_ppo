#include "UserInfoManager.h"

#include <utility>

#include "typestring.h"

#include "ValueCriteria.h"

#include "QueryableFilterGeneric.h"

#include "UserMapper.h"

#include "LoginManager.h"

#include "User.h"
#include "Human.h"
#include "UserHuman.h"

UserInfoManager::UserInfoManager(AppContext &context, UserMapper &mapper)
    : context(context), mapper(mapper)
{}

UserMapper::Map UserInfoManager::getInfo(std::string hash) const
{
    auto login = this->context.getLoginManager();

    if (!login->isAuthenticated(hash))
        throw CALL_EX(NotAuthenticatedUserInfoManagerException);

    const User &user = login->getAuthenticated(hash);

    UserMapper::Map out;

    out.emplace(std::pair<std::string, std::string>("name", user.name));
    out.emplace(std::pair<std::string, std::string>("email", user.email));

    return out;
}

void UserInfoManager::updateInfo(std::string hash, const UserMapper::Map &map)
{
    auto login = this->context.getLoginManager();

    if (!login->isAuthenticated(hash))
        throw CALL_EX(NotAuthenticatedUserInfoManagerException);

    User user = login->getAuthenticated(hash);

    for (auto item : map)
    {
        if ("name" == item.first)
            user.name = item.second;
        else if ("email" == item.first)
            user.email = item.second;
        else if ("password" == item.first)
            user.password = item.second;
        else
            throw CALL_EX(UnexpectedKeyUserInfoManagerException);
    }

    auto repo = this->context.getRepositoryContext().getUserRepository();

    repo->update(user);
}

bool UserInfoManager::isHuman(std::string hash) const
{
    return this->getUserHuman(hash).isHuman();
}

UserMapper::Map UserInfoManager::getHuman(std::string hash) const
{
    UserHuman uh = this->getUserHuman(hash);
    Human human = uh.human;
    UserMapper::Map out;

    this->mapper.map(this->context, human, out);

    return out;
}

UserHuman UserInfoManager::getUserHuman(std::string hash) const
{
    auto login = this->context.getLoginManager();

    if (!login->isAuthenticated(hash))
        throw CALL_EX(NotHumanUserInfoManagerException);

    const User &user = login->getAuthenticated(hash);
    auto repo = this->context.getRepositoryContext().getUserHumanRepository();

    ValueCriteria criteria (TypeName::getAttribute<UserHuman>("id"), "=", std::to_string(user.id));
    auto set = repo->get(criteria);

    return set->begin()->get();
}

