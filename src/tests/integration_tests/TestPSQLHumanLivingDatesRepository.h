#ifndef _TESTPSQLHUMANLIVINGDATESREPOSITORY_H_
#define _TESTPSQLHUMANLIVINGDATESREPOSITORY_H_

#include <gtest/gtest.h>
#include "test_eq.h"

#include "typestring.h"
#include "date_common.h"

#include "setupPSQLTest.h"
#include "ValueCriteria.h"

struct TestPSQLHumanLivingDatesRepository : public testing::Test {
    PSQLTestContext context;
    std::shared_ptr<IHumanLivingDatesRepository> repo;
    HumanLivingDates hld;

    void insertHumanLivingDates(void)
    {
        pqxx::work w (*context.connection);
        w.exec_params("insert into human.dates (human_id, birth, death, valid_from, source) "
                      "values ($1, $2, $3, $4, 'desktop')",
                      *hld.id, DateCommon::getTime(*hld.birthDate),
                      DateCommon::getTime(*hld.deathDate),
                      DateCommon::getTime(*hld.validFrom));
        w.commit();
    }

    void SetUp()
    {
        std::time_t now = std::time(nullptr);
        context = setupPSQLRepositories();
        repo = context.repositories->getHumanLivingDatesRepository();
        pqxx::work w (*context.connection);

        pqxx::result r = w.exec("insert into entities.human (source) values ('desktop') returning id");
        hld = HumanLivingDates(r[0][0].as<unsigned long long>(), now - 1000, now - 500, now);
        w.commit();
    }
};

TEST_F(TestPSQLHumanLivingDatesRepository, create_test)
{
    ASSERT_NO_THROW(repo->create(hld));

    pqxx::nontransaction nt (*context.connection);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from human.dates "
                        "where human_id = $1 "
                              "and birth = to_timestamp($2) "
                              "and death = to_timestamp($3) "
                              "and valid_from = to_timestamp($4)",
                        *hld.id, *hld.birthDate, *hld.deathDate,
                        *hld.validFrom);
    );
}

TEST_F(TestPSQLHumanLivingDatesRepository, update_test)
{
    insertHumanLivingDates();

    std::time_t now = std::time(nullptr) + 10;
    HumanLivingDates updated (hld.id, now - 1000, now - 500, now);

    ASSERT_NO_THROW(repo->update(updated));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from human.dates "
                             "where human_id = $1 ", *hld.id);
    );

    ASSERT_EQ(res.size(), 2);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from human.dates "
                        "where human_id = $1 "
                              "and birth = to_timestamp($2) "
                              "and death = to_timestamp($3) "
                              "and valid_from = to_timestamp($4)",
                        *updated.id, *updated.birthDate, *updated.deathDate,
                        *updated.validFrom);
    );
}

TEST_F(TestPSQLHumanLivingDatesRepository, erase_single_test)
{
    insertHumanLivingDates();

    ASSERT_NO_THROW(repo->erase(hld));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from human.dates "
                             "where human_id = $1 ", *hld.id);
    );

    ASSERT_EQ(res.size(), 1);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from human.dates "
                        "where deleted = true and human_id = $1 "
                              "and birth = to_timestamp($2) "
                              "and death = to_timestamp($3) "
                              "and valid_from = to_timestamp($4)",
                        *hld.id, *hld.birthDate, *hld.deathDate,
                        *hld.validFrom);
    );
}

TEST_F(TestPSQLHumanLivingDatesRepository, erase_strategy_test)
{
    insertHumanLivingDates();

    ValueCriteria criteria (TypeName::getAttribute<HumanLivingDates>("id"), "=", std::to_string(*hld.id));
    auto crepo = context.repositories->getHumanLivingDatesRepository();

    ASSERT_NO_THROW(crepo->erase(criteria));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from human.dates "
                             "where human_id = $1 ", *hld.id);
    );

    ASSERT_EQ(res.size(), 1);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from human.dates "
                        "where deleted = true and human_id = $1 "
                              "and birth = to_timestamp($2) "
                              "and death = to_timestamp($3) "
                              "and valid_from = to_timestamp($4)",
                        *hld.id, *hld.birthDate, *hld.deathDate,
                        *hld.validFrom);
    );
}

TEST_F(TestPSQLHumanLivingDatesRepository, get_test)
{
    insertHumanLivingDates();
    std::shared_ptr<ITimeChangeableRepositorySet<HumanLivingDates>> set = nullptr;;

    ASSERT_NO_THROW(set = repo->getAll());

    auto id_iter = set->begin(),
         id_end = set->end();

    ASSERT_NO_THROW(ASSERT_TRUE(id_end->notEqual(id_iter)));

    auto iter = set->beginId(id_iter),
         end = set->endId(id_iter);

    ASSERT_NO_THROW(ASSERT_TRUE(end->notEqual(iter)));

    ASSERT_TRUE(test_eq(hld, iter->get()));
    iter->next();
    ASSERT_NO_THROW(ASSERT_FALSE(end->notEqual(iter)));
    id_iter->next();
    ASSERT_NO_THROW(ASSERT_FALSE(id_end->notEqual(id_iter)));
}

#endif

