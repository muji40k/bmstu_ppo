#include "PSQLHumanLivingDatesRepository.h"

#include <utility>

#include "PSQLCriteriaInterpreter.h"
#include "PSQLGenericTimeChangeableIterator.h"

#include "date_common.h"

PSQLHumanLivingDatesRepository::PSQLHumanLivingDatesRepository(std::shared_ptr<pqxx::connection> connection,
                                             std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder)
    : connection(connection), builder(builder)
{
    if (nullptr == connection || nullptr == builder)
        throw CALL_EX(NullptrRepositoryException);
}

void PSQLHumanLivingDatesRepository::create(const HumanLivingDates &item)
try
{
    pqxx::work work (*this->connection);
    unsigned long long id = item.id;

    static const std::string query_entity =
    "insert into "
    "entities.human (source) "
    "values ('desktop') "
    "returning id";

    static const std::string query_general_dead =
    "insert into "
    "human.dates (human_id, birth, death, valid_from, source) "
    "values      ($1,       $2,    $3,    $4,         'desktop')";

    static const std::string query_general_alive =
    "insert into "
    "human.dates (human_id, birth, valid_from, source) "
    "values      ($1,       $2,    $3,         'desktop')";

    if (0 == id)
    {
        pqxx::row row = work.exec1(query_entity);
        id = row[0].as<unsigned long long>();
    }

    if (item.isAlive(std::time(nullptr)))
        work.exec_params(query_general_alive, id, DateCommon::getTime(*item.birthDate),
                                              DateCommon::getTime(item.validFrom));
    else
        work.exec_params(query_general_dead, id, DateCommon::getTime(*item.birthDate),
                                              DateCommon::getTime(*item.deathDate),
                                              DateCommon::getTime(item.validFrom));

    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(CreateRepositoryException, er.what());
}

void PSQLHumanLivingDatesRepository::update(const HumanLivingDates &item)
try
{
    if (0 == item.id)
        throw CALL_EX(NoObjectUpdateRepositoryException);

    pqxx::work work (*this->connection);

    static const std::string query_general_dead =
    "insert into "
    "human.dates (human_id, birth, death, valid_from, source) "
    "values      ($1,       $2,    $3,    $4,         'desktop')";

    static const std::string query_general_alive =
    "insert into "
    "human.dates (human_id, birth, valid_from, source) "
    "values      ($1,       $2,    $3,         'desktop')";

    if (item.isAlive(std::time(nullptr)))
        work.exec_params(query_general_alive, *item.id,
                                              DateCommon::getTime(*item.birthDate),
                                              DateCommon::getTime(item.validFrom));
    else
        work.exec_params(query_general_dead, *item.id,
                                              DateCommon::getTime(*item.birthDate),
                                              DateCommon::getTime(*item.deathDate),
                                              DateCommon::getTime(item.validFrom));

    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(UpdateRepositoryException, er.what());
}

void PSQLHumanLivingDatesRepository::erase(const HumanLivingDates &item)
try
{
    if (0 == item.id)
        throw CALL_EX(NoObjectEraseRepositoryException);

    pqxx::work work (*this->connection);

    static const std::string query_general =
    "update human.dates "
    "set deleted = true "
    "where human_id = $1 and valid_from = $2";

    work.exec_params(query_general, *item.id, DateCommon::getTime(item.validFrom));

    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(EraseRepositoryException, er.what());
}

void PSQLHumanLivingDatesRepository::erase(const ICriteria &criteria)
try
{
    pqxx::work work (*this->connection);
    auto interpreter = this->builder->get();

    criteria.accept(*interpreter);

    static const std::string query_general =
    "update human.dates "
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

std::shared_ptr<ITimeChangeableRepositorySet<HumanLivingDates>> PSQLHumanLivingDatesRepository::get(const ICriteria &criteria)
try
{
    auto interpreter = this->builder->get();
    criteria.accept(*interpreter);

    return std::make_shared<PSQLGenericTimeChangeableRepositorySet<HumanLivingDates>>(this->connection, interpreter->result());
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationTimeChangeableRepositorySetException);
}
catch (CommonCriteriaVisitorException &er)
{
    throw CALL_EX_MSG(WrongCriteriaTimeChangeableRepositoryException, er.what());
}

std::shared_ptr<ITimeChangeableRepositorySet<HumanLivingDates>> PSQLHumanLivingDatesRepository::getAll(void)
try
{
    return std::make_shared<PSQLGenericTimeChangeableRepositorySet<HumanLivingDates>>(this->connection);
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationTimeChangeableRepositorySetException);
}

template <>
HumanLivingDates PSQLGenericTimeChangeableRepositoryIterator<HumanLivingDates>::get(void)
{
    const pqxx::row &row = *this->iter;

    if (row["death"].is_null())
        return HumanLivingDates (row["human_id"].as<unsigned long long>(),
                                 DateCommon::parseTime(row["birth"].as<std::string>()),
                                 DateCommon::parseTime(row["valid_from"].as<std::string>()));

    return HumanLivingDates (row["human_id"].as<unsigned long long>(),
                             DateCommon::parseTime(row["birth"].as<std::string>()),
                             DateCommon::parseTime(row["death"].as<std::string>()),
                             DateCommon::parseTime(row["valid_from"].as<std::string>()));
}

template <>
std::shared_ptr<pqxx::result> PSQLGenericTimeChangeableRepositorySet<HumanLivingDates>::makeIdResult(void)
{
    const std::string query =
    "select distinct human_id as id "
    "from human.dates "
    "where (deleted = false and " + this->query + ")";

    pqxx::nontransaction nt (*this->connection);
    pqxx::result res = nt.exec(query);
    nt.commit();

    return std::make_shared<pqxx::result>(res);
}

template <>
std::shared_ptr<pqxx::result> PSQLGenericTimeChangeableRepositorySet<HumanLivingDates>::makeResult(unsigned long long id)
{
    const std::string query =
    "select * "
    "from (select *, max(modification_date) over (partition by valid_from) "
           "from human.dates "
           "where deleted = false and human_id = $1 and " + this->query + ") as filtered "
    "where modification_date = max "
    "order by valid_from desc";

    pqxx::nontransaction nt (*this->connection);
    pqxx::result res = nt.exec_params(query, id);
    nt.commit();

    return std::make_shared<pqxx::result>(res);
}

