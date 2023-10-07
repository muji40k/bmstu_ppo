#include "PSQLPlaceCountryRepository.h"

#include "PSQLCriteriaInterpreter.h"
#include "PSQLGenericTimeChangeableIterator.h"

#include "date_common.h"

PSQLPlaceCountryRepository::PSQLPlaceCountryRepository(std::shared_ptr<pqxx::connection> connection,
                                             std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder)
    : connection(connection), builder(builder)
{
    if (nullptr == connection || nullptr == builder)
        throw CALL_EX(NullptrRepositoryException);
}

void PSQLPlaceCountryRepository::create(const PlaceCountry &item)
try
{
    pqxx::work work (*this->connection);
    unsigned long long id = item.id;

    static const std::string query_entity =
    "insert into "
    "entities.place (source) "
    "values ('desktop') "
    "returning id";

    static const std::string query_general =
    "insert into "
    "place.country (place_id, country_id, valid_from, source) "
    "values        ($1,       $2,         $3,         'desktop')";

    if (0 == id)
    {
        pqxx::row row = work.exec1(query_entity);
        id = row[0].as<unsigned long long>();
    }

    work.exec_params(query_general, id, *item.country->id,
                                    DateCommon::getTime(item.validFrom));

    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(CreateRepositoryException, er.what());
}

void PSQLPlaceCountryRepository::update(const PlaceCountry &item)
try
{
    if (0 == item.id)
        throw CALL_EX(NoObjectUpdateRepositoryException);

    pqxx::work work (*this->connection);

    static const std::string query_general =
    "insert into "
    "place.country (place_id, country_id, valid_from, source) "
    "values        ($1,       $2,         $3,         'desktop')";

    work.exec_params(query_general, *item.id, *item.country->id,
                                    DateCommon::getTime(item.validFrom));

    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(UpdateRepositoryException, er.what());
}

void PSQLPlaceCountryRepository::erase(const PlaceCountry &item)
try
{
    if (0 == item.id)
        throw CALL_EX(NoObjectEraseRepositoryException);

    pqxx::work work (*this->connection);

    static const std::string query_general =
    "update place.country "
    "set deleted = true "
    "where place_id = $1 and valid_from = $2";

    work.exec_params(query_general, *item.id, DateCommon::getTime(item.validFrom));

    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(EraseRepositoryException, er.what());
}

void PSQLPlaceCountryRepository::erase(const ICriteria &criteria)
try
{
    pqxx::work work (*this->connection);
    auto interpreter = this->builder->get();

    criteria.accept(*interpreter);

    static const std::string query_general =
    "update place.country "
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

std::shared_ptr<ITimeChangeableRepositorySet<PlaceCountry>> PSQLPlaceCountryRepository::get(const ICriteria &criteria)
try
{
    auto interpreter = this->builder->get();
    criteria.accept(*interpreter);

    return std::make_shared<PSQLGenericTimeChangeableRepositorySet<PlaceCountry>>(this->connection, interpreter->result());
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationTimeChangeableRepositorySetException);
}
catch (CommonCriteriaVisitorException &er)
{
    throw CALL_EX_MSG(WrongCriteriaTimeChangeableRepositoryException, er.what());
}

std::shared_ptr<ITimeChangeableRepositorySet<PlaceCountry>> PSQLPlaceCountryRepository::getAll(void)
try
{
    return std::make_shared<PSQLGenericTimeChangeableRepositorySet<PlaceCountry>>(this->connection);
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationTimeChangeableRepositorySetException);
}

template <>
PlaceCountry PSQLGenericTimeChangeableRepositoryIterator<PlaceCountry>::get(void)
{
    const pqxx::row &row = *this->iter;

    Country country (row["country_id"].as<unsigned long long>(),
                     row["type"].as<std::string>(),
                     row["name"].as<std::string>(),
                     row["gdp"].as<double>(),
                     DateCommon::parseTime(row["cvalid_from"].as<std::string>()));

    return PlaceCountry (row["place_id"].as<unsigned long long>(),
                         country,
                         DateCommon::parseTime(row["pvalid_from"].as<std::string>()));
}

template <>
std::shared_ptr<pqxx::result> PSQLGenericTimeChangeableRepositorySet<PlaceCountry>::makeIdResult(void)
{
    const std::string query =
    "select distinct place_id as id "
    "from place.country "
    "where (deleted = false and " + this->query + ")";

    pqxx::nontransaction nt (*this->connection);
    pqxx::result res = nt.exec(query);
    nt.commit();

    return std::make_shared<pqxx::result>(res);
}

template <>
std::shared_ptr<pqxx::result> PSQLGenericTimeChangeableRepositorySet<PlaceCountry>::makeResult(unsigned long long id)
{
    const std::string query =
    "select * "
    "from (select place_id, "
                 "pfilter.country_id, "
                 "pfilter.valid_from as pvalid_from, "
                 "cfilter.name, "
                 "cfilter.type, "
                 "cfilter.gdp, "
                 "cfilter.valid_from as cvalid_from, "
                 "max(cfilter.valid_from) over (partition by pfilter.valid_from) "
          "from (select * "
                "from (select *, max(modification_date) over (partition by valid_from) "
                      "from place.country "
                      "where deleted = false and place_id = $1 and " + this->query + ") as pinner "
                "where modification_date = max) as pfilter "
            "join (select * "
                  "from (select *, max(modification_date) over (partition by country_id, valid_from) "
                        "from country.general "
                        "where deleted = false) as cinner "
                  "where modification_date = max) as cfilter "
            "on pfilter.country_id = cfilter.country_id and pfilter.valid_from >= cfilter.valid_from) as filtered "
    "where cvalid_from = max "
    "order by pvalid_from desc";

    pqxx::nontransaction nt (*this->connection);
    pqxx::result res = nt.exec_params(query, id);
    nt.commit();

    return std::make_shared<pqxx::result>(res);
}

