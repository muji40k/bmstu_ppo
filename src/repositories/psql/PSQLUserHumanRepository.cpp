#include "PSQLUserHumanRepository.h"

#include "typestring.h"

#include "PSQLCriteriaInterpreter.h"
#include "PSQLGenericIterator.h"

#include "ValueCriteria.h"

namespace PSQLUserHuman
{
    class IteratorWrap : public IRepositoryIterator<UserHuman>
    {
        public:
            IteratorWrap(std::shared_ptr<IRepositoryIterator<UserHuman>> iter,
                         std::shared_ptr<IHumanRepository> repo)
                : iter(iter), repo(repo)
            {
                if (nullptr == iter || nullptr == repo)
                    throw CALL_EX(InitializationRepositoryIteratorException);
            }

            virtual ~IteratorWrap(void) override = default;

            virtual UserHuman get(void) override
            {
                UserHuman out = this->iter->get();

                if (!out.isHuman())
                    return out;

                ValueCriteria id_criteria (TypeName::getAttribute<Human>("id"), "=", std::to_string(out.human->id));
                auto set = this->repo->get(id_criteria);

                auto id_iter = set->begin(),
                     id_end  = set->end();

                if (!id_end->notEqual(id_iter))
                    throw CALL_EX(CommonRepositorySetException);

                out.human = set->beginId(id_iter)->get();

                return out;
            }

            virtual void next() override
            {
                this->iter->next();
            }

            virtual bool notEqual(std::shared_ptr<IRepositoryIterator<UserHuman>> iter) override
            {
                std::shared_ptr<IteratorWrap> citer = std::dynamic_pointer_cast<IteratorWrap>(iter);

                if (nullptr == citer)
                    throw CALL_EX(IncompatibleRepositoryIteratorException);

                return this->iter->notEqual(citer->iter);
            }

        private:
            std::shared_ptr<IRepositoryIterator<UserHuman>> iter;
            std::shared_ptr<IHumanRepository> repo;
    };

    class SetWrap : public IRepositorySet<UserHuman>
    {
        public:
            SetWrap(std::shared_ptr<IRepositorySet<UserHuman>> set,
                         std::shared_ptr<IHumanRepository> repo)
                : set(set), repo(repo)
            {
                if (nullptr == set || nullptr == repo)
                    throw CALL_EX(InitializationRepositoryIteratorException);
            }

            virtual ~SetWrap(void) override = default;

            virtual std::shared_ptr<IRepositoryIterator<UserHuman>> begin(void) override
            try
            {
                return std::make_shared<IteratorWrap>(this->set->begin(), this->repo);
            }
            catch (std::bad_alloc &)
            {
                throw CALL_EX(AllocationRepositorySetException);
            }

            virtual std::shared_ptr<IRepositoryIterator<UserHuman>> end(void) override
            try
            {
                return std::make_shared<IteratorWrap>(this->set->end(), this->repo);
            }
            catch (std::bad_alloc &)
            {
                throw CALL_EX(AllocationRepositorySetException);
            }

        private:
            std::shared_ptr<IRepositorySet<UserHuman>> set;
            std::shared_ptr<IHumanRepository> repo;
    };
}

PSQLUserHumanRepository::PSQLUserHumanRepository(std::shared_ptr<pqxx::connection> connection,
                                                 std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder,
                                                 std::shared_ptr<IHumanRepository> repo)
    : connection(connection), builder(builder), repo(repo)
{
    if (nullptr == connection || nullptr == builder || nullptr == repo)
        throw CALL_EX(NullptrRepositoryException);
}

void PSQLUserHumanRepository::create(const UserHuman &item)
try
{
    static const std::string query =
    "insert into "
    "authentication.user_human (user_id, human_id) "
    "values                    ($1,      $2)";

    static const std::string query_not_human =
    "insert into "
    "authentication.user_human (user_id) "
    "values                    ($1)";

    pqxx::work work (*this->connection);

    if (item.isHuman())
        work.exec_params(query, *item.id, *item.human->id);
    else
        work.exec_params(query_not_human, *item.id);

    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(CreateRepositoryException, er.what());
}

void PSQLUserHumanRepository::update(const UserHuman &item)
try
{
    if (0 == item.id)
        throw CALL_EX(NoObjectUpdateRepositoryException);

    static const std::string query =
    "update authentication.user_human "
    "set human_id = $2 "
    "where user_id = $1";

    static const std::string query_not_human =
    "update authentication.user_human "
    "set human_id = null "
    "where user_id = $1";

    pqxx::work work (*this->connection);

    if (item.isHuman())
        work.exec_params(query, *item.id, *item.human->id);
    else
        work.exec_params(query_not_human, *item.id);

    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(UpdateRepositoryException, er.what());
}

void PSQLUserHumanRepository::erase(const UserHuman &item)
try
{
    if (0 == item.id)
        throw CALL_EX(NoObjectEraseRepositoryException);

    static const std::string query =
    "delete from authentication.user_human "
    "where user_id = $1";

    pqxx::work work (*this->connection);
    work.exec_params(query, *item.id);
    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(EraseRepositoryException, er.what());
}

void PSQLUserHumanRepository::erase(const ICriteria &criteria)
try
{
    static const std::string query =
    "delete from authentication.user_human where ";

    auto interpreter = this->builder->get();
    criteria.accept(*interpreter);

    pqxx::work work (*this->connection);
    work.exec_params(query + interpreter->result());
    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(EraseRepositoryException, er.what());
}
catch (CommonCriteriaVisitorException &er)
{
    throw CALL_EX_MSG(WrongCriteriaWriteRepositoryException, er.what());
}

std::shared_ptr<IRepositorySet<UserHuman>> PSQLUserHumanRepository::get(const ICriteria &criteria)
try
{
    static const std::string query =
    "select * from authentication.user_human where ";

    auto interpreter = this->builder->get();
    criteria.accept(*interpreter);

    pqxx::nontransaction nt (*this->connection);
    pqxx::result result = nt.exec_params(query + interpreter->result());
    nt.commit();

    return std::make_shared<PSQLUserHuman::SetWrap>(std::make_shared<PSQLGenericRepositorySet<UserHuman>>(std::make_shared<pqxx::result>(result)),
                                                    this->repo);
}
catch (std::bad_alloc &er)
{
    throw CALL_EX(AllocationReadRepositoryException);
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(CommonReadRepositoryException, er.what());
}
catch (CommonCriteriaVisitorException &er)
{
    throw CALL_EX_MSG(WrongCriteriaReadRepositoryException, er.what());
}

std::shared_ptr<IRepositorySet<UserHuman>> PSQLUserHumanRepository::getAll(void)
try
{
    static const std::string query = "select * from authentication.user_human";

    pqxx::nontransaction nt (*this->connection);
    pqxx::result result = nt.exec_params(query);
    nt.commit();

    return std::make_shared<PSQLUserHuman::SetWrap>(std::make_shared<PSQLGenericRepositorySet<UserHuman>>(std::make_shared<pqxx::result>(result)),
                                                    this->repo);
}
catch (std::bad_alloc &er)
{
    throw CALL_EX(AllocationReadRepositoryException);
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(CommonReadRepositoryException, er.what());
}

template <>
UserHuman PSQLGenericRepositoryIterator<UserHuman>::get(void)
try
{
    const pqxx::row &row = *this->iter;

    if (row["human_id"].is_null())
        return UserHuman(row["user_id"].as<unsigned long long>());

    Human human;
    human.id = row["human_id"].as<unsigned long long>();

    return UserHuman(row["user_id"].as<unsigned long long>(), human);
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(CommonRepositoryIteratorException, er.what());
}

