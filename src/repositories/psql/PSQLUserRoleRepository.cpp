#include "PSQLUserRoleRepository.h"

#include "PSQLCriteriaInterpreter.h"
#include "PSQLGenericIterator.h"

PSQLUserRoleRepository::PSQLUserRoleRepository(std::shared_ptr<pqxx::connection> connection,
                                             std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder)
    : connection(connection), builder(builder)
{
    if (nullptr == connection || nullptr == builder)
        throw CALL_EX(NullptrRepositoryException);
}

void PSQLUserRoleRepository::create(const UserRole &item)
try
{
    static const std::string query =
    "insert into "
    "authentication.user_roles (user_id, role) "
    "values                    ($1,      $2)";

    pqxx::work work (*this->connection);
    work.exec_params(query, *item.userId, *item.role);
    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(CreateRepositoryException, er.what());
}

void PSQLUserRoleRepository::update(const UserRole &item)
try
{
    if (0 == item.id)
        throw CALL_EX(NoObjectUpdateRepositoryException);

    static const std::string query =
    "update authentication.user_roles "
    "set user_id = $2, role = $3 "
    "where id = $1";

    pqxx::work work (*this->connection);
    work.exec_params(query, *item.id, *item.userId, *item.role);
    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(UpdateRepositoryException, er.what());
}

void PSQLUserRoleRepository::erase(const UserRole &item)
try
{
    if (0 == item.id)
        throw CALL_EX(NoObjectEraseRepositoryException);

    static const std::string query =
    "delete from authentication.user_roles "
    "where id = $1 and user_id = $2 and role = $3";

    pqxx::work work (*this->connection);
    work.exec_params(query, *item.id, *item.userId, *item.role);
    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(EraseRepositoryException, er.what());
}

void PSQLUserRoleRepository::erase(const ICriteria &criteria)
try
{
    static const std::string query =
    "delete from authentication.user_roles where ";

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

std::shared_ptr<IRepositorySet<UserRole>> PSQLUserRoleRepository::get(const ICriteria &criteria)
try
{
    static const std::string query =
    "select * from authentication.user_roles where ";

    auto interpreter = this->builder->get();
    criteria.accept(*interpreter);

    pqxx::nontransaction nt (*this->connection);
    pqxx::result result = nt.exec_params(query + interpreter->result());
    nt.commit();

    return std::make_shared<PSQLGenericRepositorySet<UserRole>>(std::make_shared<pqxx::result>(result));
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

std::shared_ptr<IRepositorySet<UserRole>> PSQLUserRoleRepository::getAll(void)
try
{
    static const std::string query = "select * from authentication.user_roles";

    pqxx::nontransaction nt (*this->connection);
    pqxx::result result = nt.exec_params(query);
    nt.commit();

    return std::make_shared<PSQLGenericRepositorySet<UserRole>>(std::make_shared<pqxx::result>(result));
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
UserRole PSQLGenericRepositoryIterator<UserRole>::get(void)
try
{
    const pqxx::row &row = *this->iter;

    return UserRole (row["id"].as<unsigned long long>(),
                     row["user_id"].as<unsigned long long>(),
                     row["role"].as<std::string>());
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(EraseRepositoryException, er.what());
}

