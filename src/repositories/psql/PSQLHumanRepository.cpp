#include "PSQLHumanRepository.h"

#include "typestring.h"

#include "PSQLCriteriaInterpreter.h"
#include "PSQLGenericTimeChangeableIterator.h"

#include "LogicCriteriaBuilder.h"
#include "ValueCriteria.h"

#include "date_common.h"

PSQLHumanRepository::PSQLHumanRepository(std::shared_ptr<pqxx::connection> connection,
                                             std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder)
    : connection(connection), builder(builder)
{
    if (nullptr == connection || nullptr == builder)
        throw CALL_EX(NullptrRepositoryException);
}

void PSQLHumanRepository::create(const Human &item)
try
{
    pqxx::work work (*this->connection);
    unsigned long long id = item.id;

    static const std::string query_entity =
    "insert into "
    "entities.human (source) "
    "values ('desktop') "
    "returning id";

    static const std::string query_name =
    "insert into "
    "human.names (human_id, first_name, last_name, patronymic, valid_from, source) "
    "values      ($1,       $2,         $3,        $4,         $5,         'desktop')";

    static const std::string query_name_npatonymic =
    "insert into "
    "human.names (human_id, first_name, last_name, valid_from, source) "
    "values      ($1,       $2,         $3,        $4,         'desktop')";

    static const std::string query_birth_place =
    "insert into "
    "human.birth_place (human_id, place_id, source) "
    "values            ($1,       $2,       'desktop')";

    if (0 == id)
    {
        pqxx::row row = work.exec1(query_entity);
        id = row[0].as<unsigned long long>();
    }

    if (item.isPatronymic())
        work.exec_params(query_name, id, *item.firstName, *item.lastName,
                                     *item.patronymic,
                                     DateCommon::getTime(item.validFrom));
    else
        work.exec_params(query_name_npatonymic, id, *item.firstName, *item.lastName,
                                                DateCommon::getTime(item.validFrom));

    work.exec_params(query_birth_place, id, *item.birthPlace->id);

    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(CreateRepositoryException, er.what());
}

void PSQLHumanRepository::update(const Human &item)
try
{
    if (0 == item.id)
        throw CALL_EX(NoObjectUpdateRepositoryException);

    pqxx::work work (*this->connection);

    static const std::string query_name =
    "insert into "
    "human.names (human_id, first_name, last_name, patronymic, valid_from, source) "
    "values      ($1,       $2,         $3,        $4,         $5,         'desktop')";

    static const std::string query_name_npatronymic =
    "insert into "
    "human.names (human_id, first_name, last_name, valid_from, source) "
    "values      ($1,       $2,         $3,        $4,         'desktop')";

    static const std::string query_birth_place =
    "insert into "
    "human.birth_place (human_id, place_id, source) "
    "values            ($1,       $2,       'desktop')";

    if (item.isPatronymic())
        work.exec_params(query_name, *item.id, *item.firstName, *item.lastName,
                                     *item.patronymic,
                                     DateCommon::getTime(item.validFrom));
    else
        work.exec_params(query_name_npatronymic,
                         *item.id, *item.firstName, *item.lastName,
                         DateCommon::getTime(item.validFrom));

    work.exec_params(query_birth_place, *item.id, *item.birthPlace->id);

    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(UpdateRepositoryException, er.what());
}

void PSQLHumanRepository::erase(const Human &item)
try
{
    if (0 == item.id)
        throw CALL_EX(NoObjectEraseRepositoryException);

    pqxx::work work (*this->connection);

    static const std::string query_name =
    "update human.names "
    "set deleted = true "
    "where human_id = $1 and valid_from = $2";
    static const std::string query_birth_place =
    "update human.birth_place "
    "set deleted = true "
    "where human_id = $1";

    work.exec_params(query_name, *item.id, DateCommon::getTime(item.validFrom));
    work.exec_params(query_birth_place, *item.id);

    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(EraseRepositoryException, er.what());
}

void PSQLHumanRepository::erase(const ICriteria &criteria)
try
{
    static const CriteriaFieldMapper
    name_link ({{TypeName::getAttribute<Human>("id"), "human.names.human_id"}}),
    birth_place_link ({{TypeName::getAttribute<Human>("id"), "human.birth_place.human_id"}});
    static const CriteriaValueStringConverter converter ({});

    pqxx::nontransaction nt (*this->connection);
    auto interpreter = this->builder->get();

    criteria.accept(*interpreter);

    const std::string query_id =
    "select human.names.human_id "
    "from human.names "
         "join human.birth_place "
         "on " + interpreter->result() + " " +
            "and human.names.deleted = false "
            "and human.birth_place.deleted = false "
            "and human.names.human_id = human.birth_place.human_id";

    static const std::string query_erase_names =
    "update human.names "
    "set deleted = true "
    "where ";

    static const std::string query_erase_birth_place =
    "update human.birth_place "
    "set deleted = true "
    "where ";

    pqxx::result res = nt.exec(query_id);
    nt.commit();

    if (res.empty())
        return;

    auto iter = res.begin();
    LogicCriteriaBuilder idcriteria_builder (std::make_shared<ValueCriteria>(TypeName::getAttribute<Human>("id"), "=", (*iter)[0].as<std::string>()));

    for (; res.end() != iter; ++iter)
        idcriteria_builder.addOR(std::make_shared<ValueCriteria>(TypeName::getAttribute<Human>("id"), "=", (*iter)[0].as<std::string>()));

    std::shared_ptr<const ICriteria> idcriteria = idcriteria_builder.get();

    PSQLCriteriaInterpreter namesinterpreter (name_link, converter),
                            placeinterpreter (birth_place_link, converter);
    idcriteria->accept(namesinterpreter);
    idcriteria->accept(placeinterpreter);

    pqxx::work work (*this->connection);
    work.exec(query_erase_names + namesinterpreter.result());
    work.exec(query_erase_birth_place + placeinterpreter.result());

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

std::shared_ptr<ITimeChangeableRepositorySet<Human>> PSQLHumanRepository::get(const ICriteria &criteria)
try
{
    auto interpreter = this->builder->get();
    criteria.accept(*interpreter);

    return std::make_shared<PSQLGenericTimeChangeableRepositorySet<Human>>(this->connection, interpreter->result());
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationTimeChangeableRepositorySetException);
}
catch (CommonCriteriaVisitorException &er)
{
    throw CALL_EX_MSG(WrongCriteriaTimeChangeableRepositoryException, er.what());
}

std::shared_ptr<ITimeChangeableRepositorySet<Human>> PSQLHumanRepository::getAll(void)
try
{
    return std::make_shared<PSQLGenericTimeChangeableRepositorySet<Human>>(this->connection);
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationTimeChangeableRepositorySetException);
}

template <>
Human PSQLGenericTimeChangeableRepositoryIterator<Human>::get(void)
{
    const pqxx::row &row = *this->iter;

    Place place (row["place_id"].as<unsigned long long>(),
                 row["type"].as<std::string>(),
                 row["name"].as<std::string>(),
                 row["area"].as<double>(),
                 row["continent"].as<std::string>(),
                 DateCommon::parseTime(row["pvalid_from"].as<std::string>()));

    if (row["patronymic"].is_null())
        return Human (row["human_id"].as<unsigned long long>(),
                      row["first_name"].as<std::string>(),
                      row["last_name"].as<std::string>(),
                      place,
                      DateCommon::parseTime(row["hvalid_from"].as<std::string>()));

    return Human (row["human_id"].as<unsigned long long>(),
                  row["first_name"].as<std::string>(),
                  row["last_name"].as<std::string>(),
                  row["patronymic"].as<std::string>(),
                  place,
                  DateCommon::parseTime(row["hvalid_from"].as<std::string>()));
}

template <>
std::shared_ptr<pqxx::result> PSQLGenericTimeChangeableRepositorySet<Human>::makeIdResult(void)
{
    const std::string query =
    "select distinct human.names.human_id as id "
    "from human.names "
         "join human.birth_place "
         "on " + this->query + " " +
            "and human.names.deleted = false "
            "and human.birth_place.deleted = false "
            "and human.names.human_id = human.birth_place.human_id";

    pqxx::nontransaction nt (*this->connection);
    pqxx::result res = nt.exec(query);
    nt.commit();

    return std::make_shared<pqxx::result>(res);
}

template <>
std::shared_ptr<pqxx::result> PSQLGenericTimeChangeableRepositorySet<Human>::makeResult(unsigned long long id)
{
    const std::string query =
    "select * "
    "from (select humanbirth.human_id, "
                 "humanbirth.first_name, "
                 "humanbirth.last_name, "
                 "humanbirth.patronymic, "
                 "humanbirth.hvalid_from, "
                 "pfilter.place_id, "
                 "pfilter.name, "
                 "pfilter.type, "
                 "pfilter.area, "
                 "pfilter.continent, "
                 "pfilter.valid_from as pvalid_from, "
                 "max(pfilter.valid_from) over (partition by humanbirth.hvalid_from) "
          "from (select * "
                "from (select human.names.human_id, "
                             "human.birth_place.place_id, "
                             "human.names.first_name, "
                             "human.names.last_name, "
                             "human.names.patronymic, "
                             "human.names.valid_from as hvalid_from, "
                             "human.names.modification_date as hmodification_date, "
                             "human.birth_place.modification_date as bmodification_date, "
                             "max(human.names.modification_date) over (partition by human.names.valid_from) as hmodmax, "
                             "max(human.birth_place.modification_date) over (partition by human.names.human_id) as bmodmax "
                      "from human.names "
                           "join human.birth_place "
                           "on " + this->query + " " +
                              "and human.names.deleted = false "
                              "and human.birth_place.deleted = false "
                              "and human.names.human_id = $1 "
                              "and human.birth_place.human_id = $1) as _inner "
                "where hmodification_date = hmodmax "
                      "and bmodification_date = bmodmax) as humanbirth "
               "join (select * "
                     "from (select *, max(modification_date) over (partition by place_id, valid_from) "
                           "from place.general "
                           "where deleted = false) as pinner "
                     "where modification_date = max) as pfilter "
               "on humanbirth.place_id = pfilter.place_id "
                  "and humanbirth.hvalid_from >= pfilter.valid_from) as _final "
    "where pvalid_from = max "
    "order by hvalid_from desc";

    pqxx::nontransaction nt (*this->connection);
    pqxx::result res = nt.exec_params(query, id);
    nt.commit();

    return std::make_shared<pqxx::result>(res);
}

