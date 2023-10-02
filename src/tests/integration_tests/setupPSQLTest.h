#ifndef _SETUPPSQLTEST_H_
#define _SETUPPSQLTEST_H_

#include <pqxx/pqxx>

#include "RepositoryContext.h"

typedef struct
{
    std::shared_ptr<RepositoryContext> repositories;
    std::shared_ptr<pqxx::connection> connection;
} PSQLTestContext;

PSQLTestContext setupPSQLRepositories(void);

#endif

