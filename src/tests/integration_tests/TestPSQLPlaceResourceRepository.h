#ifndef _TESTPSQLPLACERESOURCEREPOSITORY_H_
#define _TESTPSQLPLACERESOURCEREPOSITORY_H_

#include <gtest/gtest.h>
#include "test_eq.h"

#include "typestring.h"
#include "date_common.h"

#include "QueryableFilterGeneric.h"

#include "setupPSQLTest.h"
#include "ValueCriteria.h"

struct TestPSQLPlaceResourceRepository : public testing::Test {
    PSQLTestContext context;
    std::shared_ptr<IPlaceResourceRepository> repo;
    PlaceResource pr;
    Resource resource;

    void insertPlaceResource(void)
    {
        pqxx::work w (*context.connection);
        w.exec_params("insert into resource.general (resource_id, type, name, value, rarity, valid_from, source) "
                      "values ($1, $2, $3, $4, $5, $6, 'desktop')",
                      *resource.id, *resource.type, *resource.name, *resource.value, *resource.rarity,
                      DateCommon::getTime(*resource.validFrom));
        w.exec_params("insert into place.resource (place_id, resource_id, volume, valid_from, source) "
                      "values ($1, $2, $3, $4, 'desktop')",
                      *pr.id, *resource.id, 111,
                      DateCommon::getTime(*pr.validFrom));
        w.commit();
    }

    void SetUp()
    {
        std::time_t now = std::time(nullptr);
        context = setupPSQLRepositories();
        repo = context.repositories->getPlaceResourceRepository();
        pqxx::work w (*context.connection);

        pqxx::result r = w.exec("insert into entities.resource (source) values ('desktop') returning id");
        resource = Resource(r[0][0].as<unsigned long long>(), "type", "name", 123, "rarity", now);

        r = w.exec("insert into entities.place (source) values ('desktop') returning id");
        pr = PlaceResource(r[0][0].as<unsigned long long>(), {{resource, 111}}, now);
        w.commit();
    }
};

TEST_F(TestPSQLPlaceResourceRepository, create_test)
{
    ASSERT_NO_THROW(repo->create(pr));

    pqxx::nontransaction nt (*context.connection);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from place.resource "
                        "where place_id = $1 "
                              "and resource_id = $2 "
                              "and volume = $3 "
                              "and valid_from = to_timestamp($4)",
                        *pr.id, *resource.id, 111, *pr.validFrom);
    );
}

TEST_F(TestPSQLPlaceResourceRepository, update_test)
{
    insertPlaceResource();
    PlaceResource updated (pr);
    updated.setVolume(resource, 234);

    ASSERT_NO_THROW(repo->update(updated));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from place.resource "
                             "where place_id = $1 ", *updated.id);
    );

    ASSERT_EQ(res.size(), 2);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from place.resource "
                        "where place_id = $1 "
                              "and resource_id = $2 "
                              "and volume = $3 "
                              "and valid_from = to_timestamp($4)",
                        *updated.id, *resource.id, 234, *updated.validFrom);
    );
}

TEST_F(TestPSQLPlaceResourceRepository, erase_single_test)
{
    insertPlaceResource();

    ASSERT_NO_THROW(repo->erase(pr));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from place.resource "
                             "where place_id = $1 ", *pr.id);
    );

    ASSERT_EQ(res.size(), 1);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from place.resource "
                        "where deleted = true and place_id = $1 "
                              "and resource_id = $2 "
                              "and volume = $3 "
                              "and valid_from = to_timestamp($4)",
                        *pr.id, *resource.id, 111, *pr.validFrom);
    );
}

TEST_F(TestPSQLPlaceResourceRepository, erase_strategy_test)
{
    insertPlaceResource();

    ValueCriteria criteria (TypeName::getAttribute<PlaceResource>("id"), "=", std::to_string(*pr.id));
    auto crepo = context.repositories->getPlaceResourceRepository();

    ASSERT_NO_THROW(crepo->erase(criteria));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from place.resource "
                             "where place_id = $1 ", *pr.id);
    );

    ASSERT_EQ(res.size(), 1);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from place.resource "
                        "where deleted = true and place_id = $1 "
                              "and resource_id = $2 "
                              "and volume = $3 "
                              "and valid_from = to_timestamp($4)",
                        *pr.id, *resource.id, 111, *pr.validFrom);
    );
}

TEST_F(TestPSQLPlaceResourceRepository, get_test)
{
    insertPlaceResource();
    std::shared_ptr<ITimeChangeableRepositorySet<PlaceResource>> set = nullptr;;

    ASSERT_NO_THROW(set = repo->getAll());

    auto id_iter = set->begin(),
         id_end = set->end();

    ASSERT_NO_THROW(ASSERT_TRUE(id_end->notEqual(id_iter)));

    auto iter = set->beginId(id_iter),
         end = set->endId(id_iter);

    ASSERT_NO_THROW(ASSERT_TRUE(end->notEqual(iter)));

    const PlaceResource prc = iter->get();

    ASSERT_EQ(*pr.id, *prc.id);
    std::list<Resource> resources = prc.get(AllFilter<Resource>());
    ASSERT_EQ(resources.size(), 1);
    ASSERT_TRUE(test_eq(resource, resources.front()));
    ASSERT_EQ(prc.getVolume(resources.front()), 111);

    iter->next();
    ASSERT_NO_THROW(ASSERT_FALSE(end->notEqual(iter)));
    id_iter->next();
    ASSERT_NO_THROW(ASSERT_FALSE(id_end->notEqual(id_iter)));
}

#endif

