#include "PSQLAuthorizationHook.h"

PSQLAuthorizationHook::PSQLAuthorizationHook(std::shared_ptr<pqxx::connection> connection)
    : connection(connection)
{
    if (nullptr == connection)
        throw;
}

bool PSQLAuthorizationHook::perform(RepositoryContext &,
                                    const User &user,
                                    const std::string &name)
{
    pqxx::nontransaction nt (*this->connection);
    pqxx::row row = nt.exec_params1("select * from authentication.authorize($1, $2, $3)",
                                    name, *user.email, *user.password);
    return row[0].as<bool>();
}

