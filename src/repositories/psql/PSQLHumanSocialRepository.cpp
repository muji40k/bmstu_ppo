#include "PSQLHumanSocialRepository.h"

#include <utility>

#include "PSQLCriteriaInterpreter.h"
#include "PSQLGenericTimeChangeableIterator.h"

#include "date_common.h"

PSQLHumanSocialRepository::PSQLHumanSocialRepository(std::shared_ptr<pqxx::connection> connection,
                                             std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder)
    : connection(connection), builder(builder)
{
    if (nullptr == connection || nullptr == builder)
        throw CALL_EX(NullptrRepositoryException);
}

static std::string form_general_query(const HumanSocial &item);

void PSQLHumanSocialRepository::create(const HumanSocial &item)
try
{
    pqxx::work work (*this->connection);
    unsigned long long id = item.id;

    static const std::string query_entity =
    "insert into "
    "entities.human (source) "
    "values ('desktop') "
    "returning id";

    if (0 == id)
    {
        pqxx::row row = work.exec1(query_entity);
        id = row[0].as<unsigned long long>();
    }

    HumanSocial copy (item);
    copy.id = id;

    work.exec(form_general_query(copy));

    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(CreateRepositoryException, er.what());
}

void PSQLHumanSocialRepository::update(const HumanSocial &item)
try
{
    if (0 == item.id)
        throw CALL_EX(NoObjectUpdateRepositoryException);

    pqxx::work work (*this->connection);
    work.exec(form_general_query(item));
    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(UpdateRepositoryException, er.what());
}

void PSQLHumanSocialRepository::erase(const HumanSocial &item)
try
{
    if (0 == item.id)
        throw CALL_EX(NoObjectEraseRepositoryException);

    pqxx::work work (*this->connection);

    static const std::string query_general =
    "update human.social "
    "set deleted = true "
    "where human_id = $1 and valid_from = $2";

    work.exec_params(query_general, *item.id, DateCommon::getTime(item.validFrom));

    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(EraseRepositoryException, er.what());
}

void PSQLHumanSocialRepository::erase(const ICriteria &criteria)
try
{
    pqxx::work work (*this->connection);
    auto interpreter = this->builder->get();

    criteria.accept(*interpreter);

    static const std::string query_general =
    "update human.social "
    "set deleted = true "
    "where ";

    work.exec(query_general + interpreter->result());

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

std::shared_ptr<ITimeChangeableRepositorySet<HumanSocial>> PSQLHumanSocialRepository::get(const ICriteria &criteria)
try
{
    auto interpreter = this->builder->get();
    criteria.accept(*interpreter);

    return std::make_shared<PSQLGenericTimeChangeableRepositorySet<HumanSocial>>(this->connection, interpreter->result());
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationTimeChangeableRepositorySetException);
}
catch (CommonCriteriaVisitorException &er)
{
    throw CALL_EX_MSG(WrongCriteriaTimeChangeableRepositoryException, er.what());
}

std::shared_ptr<ITimeChangeableRepositorySet<HumanSocial>> PSQLHumanSocialRepository::getAll(void)
try
{
    return std::make_shared<PSQLGenericTimeChangeableRepositorySet<HumanSocial>>(this->connection);
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationTimeChangeableRepositorySetException);
}

template <>
HumanSocial PSQLGenericTimeChangeableRepositoryIterator<HumanSocial>::get(void)
{
    const pqxx::row &row = *this->iter;

    return HumanSocial (
        row["human_id"].as<unsigned long long>(),
        row["religion"].is_null() ? "" : row["religion"].as<std::string>(),
        row["wealth"].is_null()   ? "" : row["wealth"].as<std::string>(),
        row["literacy"].is_null() ? "" : row["literacy"].as<std::string>(),
        row["busyness"].is_null() ? "" : row["busyness"].as<std::string>(),
        DateCommon::parseTime(row["valid_from"].as<std::string>()));
}

template <>
std::shared_ptr<pqxx::result> PSQLGenericTimeChangeableRepositorySet<HumanSocial>::makeIdResult(void)
{
    const std::string query =
    "select distinct human_id as id "
    "from human.social "
    "where (deleted = false and " + this->query + ")";

    pqxx::nontransaction nt (*this->connection);
    pqxx::result res = nt.exec(query);
    nt.commit();

    return std::make_shared<pqxx::result>(res);
}

template <>
std::shared_ptr<pqxx::result> PSQLGenericTimeChangeableRepositorySet<HumanSocial>::makeResult(unsigned long long id)
{
    const std::string query =
    "select * "
    "from (select *, max(modification_date) over (partition by valid_from) "
           "from human.social "
           "where deleted = false and human_id = $1 and " + this->query + ") as filtered "
    "where modification_date = max "
    "order by valid_from desc";

    pqxx::nontransaction nt (*this->connection);
    pqxx::result res = nt.exec_params(query, id);
    nt.commit();

    return std::make_shared<pqxx::result>(res);
}

static std::string form_general_query(const HumanSocial &item)
{
    std::string query_base = "insert into human.social (source, human_id, valid_from"; // human_id, religion, wealth, literacy, busyness, valid_from, source) "
    std::string values_base = "values ('desktop', \'" + std::to_string(*item.id) + "\', \'" + DateCommon::getTime(item.validFrom) + '\'';

    if ("" != *item.religion)
    {
        query_base += ", religion";
        values_base += ", \'" + *item.religion + '\'';
    }

    if ("" != *item.wealth)
    {
        query_base += ", wealth";
        values_base += ", \'" + *item.wealth + '\'';
    }

    if ("" != *item.literacy)
    {
        query_base += ", literacy";
        values_base += ", \'" + *item.literacy + '\'';
    }

    if ("" != *item.busyness)
    {
        query_base += ", busyness";
        values_base += ", \'" + *item.busyness + '\'';
    }

    return query_base + ") " + values_base + ")";
}

