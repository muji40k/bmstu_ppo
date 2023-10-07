#include "PlainUserRequestManager.h"

#include <utility>

#include "typestring.h"

#include "ValueCriteria.h"
#include "CompositeCriteria.h"
#include "LogicCriteriaBuilder.h"

#include "LoginManager.h"
#include "AuthorizationManager.h"

#include "MergeRequest.h"

PlainUserRequestManager::PlainUserRequestManager(AppContext &context, UserMapper &mapper)
    : context(context), mapper(mapper)
{}

static std::shared_ptr<ValueCriteria> parse_argument(UserMapper::Map::const_iterator iter)
{
    static const std::unordered_map<std::string, std::string> valid_args =
    {{"first_name", TypeName::getAttribute<Human>("firstName")},
     {"last_name",  TypeName::getAttribute<Human>("lastName")},
     {"patronymic", TypeName::getAttribute<Human>("patronymic")}};

    auto viter = valid_args.find((*iter).first);

    if (valid_args.end() == viter)
        throw CALL_EX(UnspecifiedDataUserRequestManagerException);

    return std::make_shared<ValueCriteria>((*viter).second, "=", (*iter).second);
}

std::list<UserMapper::Map> PlainUserRequestManager::findHuman(std::string hash, const UserMapper::Map &data) const
{
    if (data.empty())
        throw CALL_EX(EmptyDataUserRequestManagerException);

    auto login = this->context.getLoginManager();

    if (!login->isAuthenticated(hash))
        throw CALL_EX(NotAuthenticatedUserRequestManagerException);

    auto authorizator = this->context.getAuthorizationManager();

    if (!authorizator->authorize(hash, {"plainuser"}))
        throw CALL_EX(NotAuthorizedUserRequestManagerException);

    auto iter = data.begin();

    LogicCriteriaBuilder builder (parse_argument(iter++));

    for (; data.end() != iter; ++iter)
        builder.addAND(parse_argument(iter));

    auto repo = this->context.getRepositoryContext().getHumanRepository();
    auto set = repo->get(*builder.get());
    std::list<UserMapper::Map> out;

    for (auto id_iter = set->begin(), id_end = set->end();
         id_end->notEqual(id_iter);
         id_iter->next())
    {
        out.push_back(UserMapper::Map());
        UserMapper::Map &map = out.back();

        const Human human = set->beginId(id_iter)->get();

        map.emplace(std::pair("id", std::to_string(id_iter->get())));
        mapper.map(this->context, human, map);
    }

    return out;
}

void PlainUserRequestManager::setHuman(std::string hash, const UserMapper::Map &data) const
{
    if (data.empty())
        throw CALL_EX(EmptyDataUserRequestManagerException);

    auto iter = data.find("id");

    if (data.end() == iter)
        throw CALL_EX(UnsuitableDataUserRequestManagerException);

    auto login = this->context.getLoginManager();

    if (!login->isAuthenticated(hash))
        throw CALL_EX(NotAuthenticatedUserRequestManagerException);

    auto authorizator = this->context.getAuthorizationManager();

    if (!authorizator->authorize(hash, {"plainuser"}))
        throw CALL_EX(NotAuthorizedUserRequestManagerException);

    const User user = login->getAuthenticated(hash);

    ValueCriteria criteria (TypeName::getAttribute<Human>("id"), "=", (*iter).second);
    auto human_repo = this->context.getRepositoryContext().getHumanRepository();

    auto set = human_repo->get(criteria);
    auto id_iter = set->begin();

    if (!set->end()->notEqual(id_iter))
        throw CALL_EX(NotFoundUserRequestManagerException);

    const Human human = set->beginId(id_iter)->get();

    auto mr_repo = this->context.getRepositoryContext().getMergeRequestRepository();
    mr_repo->create(MergeRequest (0, user, human, "new"));
}

