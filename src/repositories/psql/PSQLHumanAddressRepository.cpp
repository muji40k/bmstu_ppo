#include "PSQLHumanAddressRepository.h"

#include "PSQLCriteriaInterpreter.h"
#include "PSQLGenericTimeChangeableIterator.h"

#include "date_common.h"

PSQLHumanAddressRepository::PSQLHumanAddressRepository(std::shared_ptr<pqxx::connection> connection,
                                             std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder)
    : connection(connection), builder(builder)
{
    if (nullptr == connection || nullptr == builder)
        throw CALL_EX(NullptrRepositoryException);
}

void PSQLHumanAddressRepository::create(const HumanAddress &item)
try
{
    pqxx::work work (*this->connection);
    unsigned long long id = item.id;

    static const std::string query_entity =
    "insert into "
    "entities.human (source) "
    "values ('desktop') "
    "returning id";

    static const std::string query_general =
    "insert into "
    "human.address (human_id, place_id, valid_from, source) "
    "values        ($1,       $2,       $3,         'desktop')";

    if (0 == id)
    {
        pqxx::row row = work.exec1(query_entity);
        id = row[0].as<unsigned long long>();
    }

    work.exec_params(query_general, id, *item.currentPlace->id,
                                    DateCommon::getTime(item.validFrom));

    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(CreateRepositoryException, er.what());
}

void PSQLHumanAddressRepository::update(const HumanAddress &item)
try
{
    if (0 == item.id)
        throw CALL_EX(NoObjectUpdateRepositoryException);

    pqxx::work work (*this->connection);

    static const std::string query_general =
    "insert into "
    "human.address (human_id, place_id, valid_from, source) "
    "values        ($1,       $2,       $3,         'desktop')";

    work.exec_params(query_general, *item.id, *item.currentPlace->id,
                                    DateCommon::getTime(item.validFrom));

    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(UpdateRepositoryException, er.what());
}

void PSQLHumanAddressRepository::erase(const HumanAddress &item)
try
{
    if (0 == item.id)
        throw CALL_EX(NoObjectEraseRepositoryException);

    pqxx::work work (*this->connection);

    static const std::string query_general =
    "update human.address "
    "set deleted = true "
    "where human_id = $1 and valid_from = $2";

    work.exec_params(query_general, *item.id, DateCommon::getTime(item.validFrom));

    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(EraseRepositoryException, er.what());
}

void PSQLHumanAddressRepository::erase(const ICriteria &criteria)
try
{
    pqxx::work work (*this->connection);
    auto interpreter = this->builder->get();

    criteria.accept(*interpreter);

    static const std::string query_general =
    "update human.address "
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

std::shared_ptr<ITimeChangeableRepositorySet<HumanAddress>> PSQLHumanAddressRepository::get(const ICriteria &criteria)
try
{
    auto interpreter = this->builder->get();
    criteria.accept(*interpreter);

    return std::make_shared<PSQLGenericTimeChangeableRepositorySet<HumanAddress>>(this->connection, interpreter->result());
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationTimeChangeableRepositorySetException);
}
catch (CommonCriteriaVisitorException &er)
{
    throw CALL_EX_MSG(WrongCriteriaTimeChangeableRepositoryException, er.what());
}

std::shared_ptr<ITimeChangeableRepositorySet<HumanAddress>> PSQLHumanAddressRepository::getAll(void)
try
{
    return std::make_shared<PSQLGenericTimeChangeableRepositorySet<HumanAddress>>(this->connection);
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationTimeChangeableRepositorySetException);
}

template <>
HumanAddress PSQLGenericTimeChangeableRepositoryIterator<HumanAddress>::get(void)
{
    const pqxx::row &row = *this->iter;

    Place place (row["place_id"].as<unsigned long long>(),
                 row["type"].as<std::string>(),
                 row["name"].as<std::string>(),
                 row["area"].as<double>(),
                 row["continent"].as<std::string>(),
                 DateCommon::parseTime(row["pvalid_from"].as<std::string>()));

    return HumanAddress (row["human_id"].as<unsigned long long>(),
                         place,
                         DateCommon::parseTime(row["hvalid_from"].as<std::string>()));
}

template <>
std::shared_ptr<pqxx::result> PSQLGenericTimeChangeableRepositorySet<HumanAddress>::makeIdResult(void)
{
    const std::string query =
    "select distinct human_id as id "
    "from human.address "
    "where (deleted = false and " + this->query + ")";

    pqxx::nontransaction nt (*this->connection);
    pqxx::result res = nt.exec(query);
    nt.commit();

    return std::make_shared<pqxx::result>(res);
}

template <>
std::shared_ptr<pqxx::result> PSQLGenericTimeChangeableRepositorySet<HumanAddress>::makeResult(unsigned long long id)
{
    const std::string query =
    "select * "
    "from (select human_id, "
                 "hfilter.place_id, "
                 "hfilter.valid_from as hvalid_from, "
                 "pfilter.name, "
                 "pfilter.type, "
                 "pfilter.area, "
                 "pfilter.continent, "
                 "pfilter.valid_from as pvalid_from, "
                 "max(pfilter.valid_from) over (partition by hfilter.valid_from) "
          "from (select * "
                "from (select *, max(modification_date) over (partition by valid_from) "
                      "from human.address "
                      "where deleted = false and human_id = $1 and " + this->query + ") as hinner "
                "where modification_date = max) as hfilter "
            "join (select * "
                  "from (select *, max(modification_date) over (partition by place_id, valid_from) "
                        "from place.general "
                        "where deleted = false) as pinner "
                  "where modification_date = max) as pfilter "
            "on hfilter.place_id = pfilter.place_id and hfilter.valid_from >= pfilter.valid_from) as filtered "
    "where pvalid_from = max "
    "order by hvalid_from desc";

    pqxx::nontransaction nt (*this->connection);
    pqxx::result res = nt.exec_params(query, id);
    nt.commit();

    return std::make_shared<pqxx::result>(res);
}

