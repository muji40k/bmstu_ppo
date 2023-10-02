#include "PSQLLanguageRepository.h"

#include "PSQLCriteriaInterpreter.h"
#include "PSQLGenericTimeChangeableIterator.h"

#include "date_common.h"

PSQLLanguageRepository::PSQLLanguageRepository(std::shared_ptr<pqxx::connection> connection,
                                             std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder)
    : connection(connection), builder(builder)
{
    if (nullptr == connection || nullptr == builder)
        throw CALL_EX(NullptrRepositoryException);
}

void PSQLLanguageRepository::create(const Language &item)
try
{
    pqxx::work work (*this->connection);
    unsigned long long id = item.id;

    static const std::string query_entity =
    "insert into "
    "entities.language (source) "
    "values ('desktop') "
    "returning id";

    static const std::string query_general =
    "insert into "
    "language.general (language_id, name, family, valid_from, source) "
    "values           ($1,          $2,   $3,     $4,         'desktop')";

    if (0 == id)
    {
        pqxx::row row = work.exec1(query_entity);
        id = row[0].as<unsigned long long>();
    }

    work.exec_params(query_general, id, *item.name, *item.family,
                                    DateCommon::getTime(item.validFrom));

    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(CreateRepositoryException, er.what());
}

void PSQLLanguageRepository::update(const Language &item)
try
{
    if (0 == item.id)
        throw CALL_EX(NoObjectUpdateRepositoryException);

    pqxx::work work (*this->connection);

    static const std::string query_general =
    "insert into "
    "language.general (language_id, name, family, valid_from, source) "
    "values           ($1,          $2,   $3,     $4,         'desktop')";

    work.exec_params(query_general, *item.id, *item.name, *item.family,
                                    DateCommon::getTime(item.validFrom));

    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(UpdateRepositoryException, er.what());
}

void PSQLLanguageRepository::erase(const Language &item)
try
{
    if (0 == item.id)
        throw CALL_EX(NoObjectEraseRepositoryException);

    pqxx::work work (*this->connection);

    static const std::string query_general =
    "update language.general "
    "set deleted = true "
    "where language_id = $1 and valid_from = $2";

    work.exec_params(query_general, *item.id, DateCommon::getTime(item.validFrom));

    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(EraseRepositoryException, er.what());
}

void PSQLLanguageRepository::erase(const ICriteria &criteria)
try
{
    pqxx::work work (*this->connection);
    auto interpreter = this->builder->get();

    criteria.accept(*interpreter);

    static const std::string query_general =
    "update language.general "
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

std::shared_ptr<ITimeChangeableRepositorySet<Language>> PSQLLanguageRepository::get(const ICriteria &criteria)
try
{
    auto interpreter = this->builder->get();
    criteria.accept(*interpreter);

    return std::make_shared<PSQLGenericTimeChangeableRepositorySet<Language>>(this->connection, interpreter->result());
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationTimeChangeableRepositorySetException);
}
catch (CommonCriteriaVisitorException &er)
{
    throw CALL_EX_MSG(WrongCriteriaTimeChangeableRepositoryException, er.what());
}

std::shared_ptr<ITimeChangeableRepositorySet<Language>> PSQLLanguageRepository::getAll(void)
try
{
    return std::make_shared<PSQLGenericTimeChangeableRepositorySet<Language>>(this->connection);
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationTimeChangeableRepositorySetException);
}

template <>
Language PSQLGenericTimeChangeableRepositoryIterator<Language>::get(void)
{
    const pqxx::row &row = *this->iter;

    return Language (row["language_id"].as<unsigned long long>(),
                     row["name"].as<std::string>(),
                     row["family"].as<std::string>(),
                     DateCommon::parseTime(row["valid_from"].as<std::string>()));
}

template <>
std::shared_ptr<pqxx::result> PSQLGenericTimeChangeableRepositorySet<Language>::makeIdResult(void)
{
    const std::string query =
    "select distinct language_id as id "
    "from language.general "
    "where (deleted = false and " + this->query + ")";

    pqxx::nontransaction nt (*this->connection);
    pqxx::result res = nt.exec(query);
    nt.commit();

    return std::make_shared<pqxx::result>(res);
}

template <>
std::shared_ptr<pqxx::result> PSQLGenericTimeChangeableRepositorySet<Language>::makeResult(unsigned long long id)
{
    const std::string query =
    "select * "
    "from (select *, max(modification_date) over (partition by valid_from) "
           "from language.general "
           "where deleted = false and language_id = $1 and " + this->query + ") as filtered "
    "where modification_date = max "
    "order by valid_from desc";

    pqxx::nontransaction nt (*this->connection);
    pqxx::result res = nt.exec_params(query, id);
    nt.commit();

    return std::make_shared<pqxx::result>(res);
}

