#ifndef _TESTPSQLPLACEREPOSITORY_H_
#define _TESTPSQLPLACEREPOSITORY_H_

#include <gtest/gtest.h>
#include "test_eq.h"

#include "typestring.h"
#include "date_common.h"

#include "setupPSQLTest.h"
#include "ValueCriteria.h"

struct TestPSQLPlaceRepository : public testing::Test {
    PSQLTestContext context;
    std::shared_ptr<IPlaceRepository> repo;
    Place place;

    void insertPlace(void)
    {
        pqxx::work w (*context.connection);
        w.exec_params("insert into place.general (place_id, type, name, area, continent, valid_from, source) "
                      "values ($1, $2, $3, $4, $5, $6, 'desktop')",
                      *place.id, *place.type, *place.name, *place.area, *place.continent,
                      DateCommon::getTime(*place.validFrom));
        w.commit();
    }

    void SetUp()
    {
        std::time_t now = std::time(nullptr);
        context = setupPSQLRepositories();
        repo = context.repositories->getPlaceRepository();
        pqxx::work w (*context.connection);

        pqxx::result r = w.exec("insert into entities.place (source) values ('desktop') returning id");
        place = Place(r[0][0].as<unsigned long long>(), "type", "name", 123, "continent", now);
        w.commit();
    }
};

TEST_F(TestPSQLPlaceRepository, create_test)
{
    ASSERT_NO_THROW(repo->create(place));

    pqxx::nontransaction nt (*context.connection);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from place.general "
                        "where place_id = $1 "
                              "and type = $2 "
                              "and name = $3 "
                              "and area = $4 "
                              "and continent = $5 "
                              "and valid_from = to_timestamp($6)",
                        *place.id, *place.type, *place.name, *place.area, *place.continent,
                        *place.validFrom);
    );
}

TEST_F(TestPSQLPlaceRepository, update_test)
{
    insertPlace();
    Place updated (place.id, "update", "update", 789, "update", std::time(nullptr));

    ASSERT_NO_THROW(repo->update(updated));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from place.general "
                             "where place_id = $1 ", *place.id);
    );

    ASSERT_EQ(res.size(), 2);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from place.general "
                        "where place_id = $1 "
                              "and type = $2 "
                              "and name = $3 "
                              "and area = $4 "
                              "and continent = $5 "
                              "and valid_from = to_timestamp($6)",
                        *updated.id, *updated.type, *updated.name, *updated.area, *updated.continent,
                        *updated.validFrom);
    );
}

TEST_F(TestPSQLPlaceRepository, erase_single_test)
{
    insertPlace();

    ASSERT_NO_THROW(repo->erase(place));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from place.general "
                             "where place_id = $1 ", *place.id);
    );

    ASSERT_EQ(res.size(), 1);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from place.general "
                        "where deleted = true and place_id = $1 "
                              "and type = $2 "
                              "and name = $3 "
                              "and area = $4 "
                              "and continent = $5 "
                              "and valid_from = to_timestamp($6)",
                        *place.id, *place.type, *place.name, *place.area, *place.continent,
                        *place.validFrom);
    );
}

TEST_F(TestPSQLPlaceRepository, erase_strategy_test)
{
    insertPlace();

    ValueCriteria criteria (TypeName::getAttribute<Place>("id"), "=", std::to_string(*place.id));
    auto crepo = context.repositories->getPlaceRepository();

    ASSERT_NO_THROW(crepo->erase(criteria));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from place.general "
                             "where place_id = $1 ", *place.id);
    );

    ASSERT_EQ(res.size(), 1);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from place.general "
                        "where deleted = true and place_id = $1 "
                              "and type = $2 "
                              "and name = $3 "
                              "and area = $4 "
                              "and continent = $5 "
                              "and valid_from = to_timestamp($6)",
                        *place.id, *place.type, *place.name, *place.area, *place.continent,
                        *place.validFrom);
    );
}

TEST_F(TestPSQLPlaceRepository, get_test)
{
    insertPlace();
    std::shared_ptr<ITimeChangeableRepositorySet<Place>> set = nullptr;;

    ASSERT_NO_THROW(set = repo->getAll());

    auto id_iter = set->begin(),
         id_end = set->end();

    ASSERT_NO_THROW(ASSERT_TRUE(id_end->notEqual(id_iter)));

    auto iter = set->beginId(id_iter),
         end = set->endId(id_iter);

    ASSERT_NO_THROW(ASSERT_TRUE(end->notEqual(iter)));

    ASSERT_TRUE(test_eq(place, iter->get()));
    iter->next();
    ASSERT_NO_THROW(ASSERT_FALSE(end->notEqual(iter)));
    id_iter->next();
    ASSERT_NO_THROW(ASSERT_FALSE(id_end->notEqual(id_iter)));
}

#endif

