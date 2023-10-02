#ifndef _TESTPSQLHUMANADDRESSREPOSITORY_H_
#define _TESTPSQLHUMANADDRESSREPOSITORY_H_

#include <gtest/gtest.h>
#include "test_eq.h"

#include "typestring.h"
#include "date_common.h"

#include "setupPSQLTest.h"
#include "ValueCriteria.h"

struct TestPSQLHumanAddressRepository : public testing::Test {
    PSQLTestContext context;
    std::shared_ptr<IHumanAddressRepository> repo;
    HumanAddress ha;

    void insertHumanAddress(void)
    {
        pqxx::work w (*context.connection);
        w.exec_params("insert into human.address (human_id, place_id, valid_from, source) "
                      "values ($1, $2, $3, 'desktop')",
                      *ha.id, *ha.currentPlace->id,
                      DateCommon::getTime(*ha.validFrom));
        const Place &place = ha.currentPlace;
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
        repo = context.repositories->getHumanAddressRepository();
        pqxx::work w (*context.connection);

        pqxx::result r = w.exec("insert into entities.place (source) values ('desktop') returning id");
        Place place (r[0][0].as<unsigned long long>(), "type", "name", 123, "continent", now);

        r = w.exec("insert into entities.human (source) values ('desktop') returning id");
        ha = HumanAddress(r[0][0].as<unsigned long long>(), place, now);
        w.commit();
    }
};

TEST_F(TestPSQLHumanAddressRepository, create_test)
{
    ASSERT_NO_THROW(repo->create(ha));

    pqxx::nontransaction nt (*context.connection);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from human.address "
                        "where human_id = $1 "
                              "and place_id = $2 "
                              "and valid_from = to_timestamp($3)",
                        *ha.id, *ha.currentPlace->id, *ha.validFrom);
    );
}

TEST_F(TestPSQLHumanAddressRepository, update_test)
{
    insertHumanAddress();
    std::time_t now = std::time(nullptr);
    pqxx::work w (*context.connection);
    pqxx::result r = w.exec("insert into entities.place (source) values ('desktop') returning id");
    Place place (r[0][0].as<unsigned long long>(), "update", "update", 567, "update", now);
    w.exec_params("insert into place.general (place_id, type, name, area, continent, valid_from, source) "
                  "values ($1, $2, $3, $4, $5, $6, 'desktop')",
                  *place.id, *place.type, *place.name, *place.area, *place.continent,
                  DateCommon::getTime(*place.validFrom));
    w.commit();
    HumanAddress updated (ha.id, place, now);

    ASSERT_NO_THROW(repo->update(updated));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from human.address "
                             "where human_id = $1 ", *updated.id);
    );

    ASSERT_EQ(res.size(), 2);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from human.address "
                        "where human_id = $1 "
                              "and place_id = $2 "
                              "and valid_from = to_timestamp($3)",
                        *updated.id, *updated.currentPlace->id, *updated.validFrom);
    );
}

TEST_F(TestPSQLHumanAddressRepository, erase_single_test)
{
    insertHumanAddress();

    ASSERT_NO_THROW(repo->erase(ha));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from human.address "
                             "where human_id = $1 ", *ha.id);
    );

    ASSERT_EQ(res.size(), 1);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from human.address "
                        "where deleted = true and human_id = $1 "
                              "and place_id = $2 "
                              "and valid_from = to_timestamp($3)",
                        *ha.id, *ha.currentPlace->id, *ha.validFrom);
    );
}

TEST_F(TestPSQLHumanAddressRepository, erase_strategy_test)
{
    insertHumanAddress();

    ValueCriteria criteria (TypeName::getAttribute<HumanAddress>("id"), "=", std::to_string(*ha.id));
    auto crepo = context.repositories->getHumanAddressRepository();

    ASSERT_NO_THROW(crepo->erase(criteria));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from human.address "
                             "where human_id = $1 ", *ha.id);
    );

    ASSERT_EQ(res.size(), 1);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from human.address "
                        "where deleted = true and human_id = $1 "
                              "and place_id = $2 "
                              "and valid_from = to_timestamp($3)",
                        *ha.id, *ha.currentPlace->id, *ha.validFrom);
    );
}

TEST_F(TestPSQLHumanAddressRepository, get_test)
{
    insertHumanAddress();
    std::shared_ptr<ITimeChangeableRepositorySet<HumanAddress>> set = nullptr;;

    ASSERT_NO_THROW(set = repo->getAll());

    auto id_iter = set->begin(),
         id_end = set->end();

    ASSERT_NO_THROW(ASSERT_TRUE(id_end->notEqual(id_iter)));

    auto iter = set->beginId(id_iter),
         end = set->endId(id_iter);

    ASSERT_NO_THROW(ASSERT_TRUE(end->notEqual(iter)));

    ASSERT_TRUE(test_eq(ha, iter->get()));
    iter->next();
    ASSERT_NO_THROW(ASSERT_FALSE(end->notEqual(iter)));
    id_iter->next();
    ASSERT_NO_THROW(ASSERT_FALSE(id_end->notEqual(id_iter)));
}

#endif

