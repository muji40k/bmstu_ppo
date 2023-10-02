#ifndef _TESTPSQLRESOURCEREPOSITORY_H_
#define _TESTPSQLRESOURCEREPOSITORY_H_

#include <gtest/gtest.h>
#include "test_eq.h"

#include "typestring.h"
#include "date_common.h"

#include "setupPSQLTest.h"
#include "ValueCriteria.h"

struct TestPSQLResourceRepository : public testing::Test {
    PSQLTestContext context;
    Resource resource;

    void insertResource(void)
    {
        pqxx::work w (*context.connection);
        w.exec_params("insert into resource.general (resource_id, name, type, value, rarity, valid_from, source) "
                      "values ($1, $2, $3, $4, $5, $6, 'desktop')",
                      *resource.id, *resource.name, *resource.type, *resource.value, *resource.rarity,
                      DateCommon::getTime(*resource.validFrom));
        w.commit();
    }

    void SetUp()
    {
        std::time_t now = std::time(nullptr);
        context = setupPSQLRepositories();
        pqxx::work w (*context.connection);

        pqxx::result r = w.exec("insert into entities.resource (source) values ('desktop') returning id");
        resource = Resource(r[0][0].as<unsigned long long>(), "type", "name", 123, "rarity", now);
        w.commit();
    }
};

TEST_F(TestPSQLResourceRepository, create_test)
{
    auto crepo = context.repositories->getResourceRepository();

    ASSERT_NO_THROW(crepo->create(resource));

    pqxx::nontransaction nt (*context.connection);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from resource.general "
                        "where resource_id = $1 "
                              "and type = $2 "
                              "and name = $3 "
                              "and value = $4 "
                              "and rarity = $5 "
                              "and valid_from = $6",
                        *resource.id, *resource.type, *resource.name, *resource.value, *resource.rarity,
                        DateCommon::getTime(*resource.validFrom));
    );
}

TEST_F(TestPSQLResourceRepository, update_test)
{
    insertResource();

    Resource updated (resource.id, "new", "new", 789, "new", std::time(nullptr));

    auto crepo = context.repositories->getResourceRepository();

    ASSERT_NO_THROW(crepo->update(updated));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from resource.general "
                             "where resource_id = $1 ", *resource.id);
    );

    ASSERT_EQ(res.size(), 2);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from resource.general "
                        "where resource_id = $1 "
                              "and type = $2 "
                              "and name = $3 "
                              "and value = $4 "
                              "and rarity = $5 "
                              "and valid_from = $6",
                        *updated.id, *updated.type, *updated.name, *updated.value, *updated.rarity,
                        DateCommon::getTime(*updated.validFrom));
    );
}

TEST_F(TestPSQLResourceRepository, erase_single_test)
{
    insertResource();

    auto crepo = context.repositories->getResourceRepository();

    ASSERT_NO_THROW(crepo->erase(resource));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from resource.general "
                             "where resource_id = $1 ", *resource.id);
    );

    ASSERT_EQ(res.size(), 1);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from resource.general "
                        "where deleted = true "
                              "and resource_id = $1 "
                              "and type = $2 "
                              "and name = $3 "
                              "and value = $4 "
                              "and rarity = $5 "
                              "and valid_from = $6",
                        *resource.id, *resource.type, *resource.name, *resource.value, *resource.rarity,
                        DateCommon::getTime(*resource.validFrom));
    );

    ASSERT_EQ(res.size(), 1);
}

TEST_F(TestPSQLResourceRepository, erase_strategy_test)
{
    insertResource();

    ValueCriteria criteria (TypeName::getAttribute<Resource>("id"), "=", std::to_string(*resource.id));
    auto crepo = context.repositories->getResourceRepository();

    ASSERT_NO_THROW(crepo->erase(criteria));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from resource.general "
                             "where resource_id = $1 ", *resource.id);
    );

    ASSERT_EQ(res.size(), 1);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from resource.general "
                        "where deleted = true "
                              "and resource_id = $1 "
                              "and type = $2 "
                              "and name = $3 "
                              "and value = $4 "
                              "and rarity = $5 "
                              "and valid_from = $6",
                        *resource.id, *resource.type, *resource.name, *resource.value, *resource.rarity,
                        DateCommon::getTime(*resource.validFrom));
    );

    ASSERT_EQ(res.size(), 1);
}

TEST_F(TestPSQLResourceRepository, get_test)
{
    insertResource();

    auto rrepo = context.repositories->getResourceRepository();
    std::shared_ptr<ITimeChangeableRepositorySet<Resource>> set = nullptr;;

    ASSERT_NO_THROW(set = rrepo->getAll());

    auto id_iter = set->begin(),
         id_end = set->end();

    ASSERT_NO_THROW(ASSERT_TRUE(id_end->notEqual(id_iter)));

    auto iter = set->beginId(id_iter),
         end = set->endId(id_iter);

    ASSERT_NO_THROW(ASSERT_TRUE(end->notEqual(iter)));

    ASSERT_TRUE(test_eq(resource, iter->get()));
    iter->next();
    ASSERT_NO_THROW(ASSERT_FALSE(end->notEqual(iter)));
    id_iter->next();
    ASSERT_NO_THROW(ASSERT_FALSE(id_end->notEqual(id_iter)));
}

#endif

