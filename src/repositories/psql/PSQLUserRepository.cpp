#include "PSQLUserRepository.h"

#include "PSQLCriteriaInterpreter.h"
#include "PSQLGenericIterator.h"

PSQLUserRepository::PSQLUserRepository(std::shared_ptr<pqxx::connection> connection,
                                             std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder)
    : connection(connection), builder(builder)
{
    if (nullptr == connection || nullptr == builder)
        throw CALL_EX(NullptrRepositoryException);
}

void PSQLUserRepository::create(const User &item)
try
{
    static const std::string query =
    "insert into "
    "authentication.users (email, password, name) "
    "values               ($1,    $2,       $3)";

    pqxx::work work (*this->connection);
    work.exec_params(query, *item.email, *item.password, *item.name);
    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(CreateRepositoryException, er.what());
}

void PSQLUserRepository::update(const User &item)
try
{
    if (0 == item.id)
        throw CALL_EX(NoObjectUpdateRepositoryException);

    static const std::string query =
    "update authentication.users "
    "set email = $2, password = $3, name = $4 "
    "where id = $1";

    pqxx::work work (*this->connection);
    work.exec_params(query, *item.id, *item.email, *item.password, *item.name);
    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(UpdateRepositoryException, er.what());
}

void PSQLUserRepository::erase(const User &item)
try
{
    if (0 == item.id)
        throw CALL_EX(NoObjectEraseRepositoryException);

    static const std::string query =
    "delete from authentication.users "
    "where id = $1 and email = $2 and password = $3 and name = $4";

    pqxx::work work (*this->connection);
    work.exec_params(query, *item.id, *item.email, *item.password, *item.name);
    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(EraseRepositoryException, er.what());
}

void PSQLUserRepository::erase(const ICriteria &criteria)
try
{
    static const std::string query =
    "delete from authentication.users where ";

    auto interpreter = this->builder->get();
    criteria.accept(*interpreter);

    pqxx::work work (*this->connection);
    work.exec_params(query + interpreter->result());
    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(CommonReadRepositoryException, er.what());
}
catch (CommonCriteriaVisitorException &er)
{
    throw CALL_EX_MSG(WrongCriteriaWriteRepositoryException, er.what());
}

std::shared_ptr<IRepositorySet<User>> PSQLUserRepository::get(const ICriteria &criteria)
try
{
    static const std::string query =
    "select * from authentication.users where ";

    auto interpreter = this->builder->get();
    criteria.accept(*interpreter);

    pqxx::nontransaction nt (*this->connection);
    pqxx::result result = nt.exec_params(query + interpreter->result());
    nt.commit();

    return std::make_shared<PSQLGenericRepositorySet<User>>(std::make_shared<pqxx::result>(result));
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

std::shared_ptr<IRepositorySet<User>> PSQLUserRepository::getAll(void)
try
{
    static const std::string query = "select * from authentication.users";

    pqxx::nontransaction nt (*this->connection);
    pqxx::result result = nt.exec_params(query);
    nt.commit();

    return std::make_shared<PSQLGenericRepositorySet<User>>(std::make_shared<pqxx::result>(result));
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
User PSQLGenericRepositoryIterator<User>::get(void)
try
{
    const pqxx::row &row = *this->iter;

    return User (row["id"].as<unsigned long long>(),
                 row["name"].as<std::string>(),
                 row["password"].as<std::string>(),
                 row["email"].as<std::string>());
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(CommonReadRepositoryException, er.what());
}

