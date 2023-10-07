#ifndef _TESTPSQLHUMANGENERALREPOSITORY_H_
#define _TESTPSQLHUMANGENERALREPOSITORY_H_

#include <gtest/gtest.h>
#include "test_eq.h"

#include "typestring.h"
#include "date_common.h"

#include "setupPSQLTest.h"
#include "ValueCriteria.h"

struct TestPSQLHumanGeneralRepository : public testing::Test {
    PSQLTestContext context;
    std::shared_ptr<IHumanGeneralRepository> repo;
    HumanGeneral hg;

    void insertHumanGeneral(void)
    {
        pqxx::work w (*context.connection);
        w.exec_params("insert into human.general (human_id, blood_type, gender, race, valid_from, source) "
                      "values ($1, $2, $3, $4, $5, 'desktop')",
                      *hg.id, *hg.bloodType, *hg.gender, *hg.race,
                      DateCommon::getTime(*hg.validFrom));
        w.commit();
    }

    void SetUp()
    {
        std::time_t now = std::time(nullptr);
        context = setupPSQLRepositories();
        repo = context.repositories->getHumanGeneralRepository();
        pqxx::work w (*context.connection);

        pqxx::result r = w.exec("insert into entities.human (source) values ('desktop') returning id");
        hg = HumanGeneral(r[0][0].as<unsigned long long>(), "blood_type", "gender", "race", now);
        w.commit();
    }
};

TEST_F(TestPSQLHumanGeneralRepository, create_test)
{
    ASSERT_NO_THROW(repo->create(hg));

    pqxx::nontransaction nt (*context.connection);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from human.general "
                        "where human_id = $1 "
                              "and blood_type = $2 "
                              "and gender = $3 "
                              "and race = $4 "
                              "and valid_from = to_timestamp($5)",
                        *hg.id, *hg.bloodType, *hg.gender, *hg.race,
                        *hg.validFrom);
    );
}

TEST_F(TestPSQLHumanGeneralRepository, update_test)
{
    insertHumanGeneral();
    HumanGeneral updated (hg.id, "update", "update", "update", std::time(nullptr));

    ASSERT_NO_THROW(repo->update(updated));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from human.general "
                             "where human_id = $1 ", *hg.id);
    );

    ASSERT_EQ(res.size(), 2);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from human.general "
                        "where human_id = $1 "
                              "and blood_type = $2 "
                              "and gender = $3 "
                              "and race = $4 "
                              "and valid_from = to_timestamp($5)",
                        *updated.id, *updated.bloodType, *updated.gender, *updated.race,
                        *updated.validFrom);
    );
}

TEST_F(TestPSQLHumanGeneralRepository, erase_single_test)
{
    insertHumanGeneral();

    ASSERT_NO_THROW(repo->erase(hg));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from human.general "
                             "where human_id = $1 ", *hg.id);
    );

    ASSERT_EQ(res.size(), 1);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from human.general "
                        "where deleted = true and human_id = $1 "
                              "and blood_type = $2 "
                              "and gender = $3 "
                              "and race = $4 "
                              "and valid_from = to_timestamp($5)",
                        *hg.id, *hg.bloodType, *hg.gender, *hg.race,
                        *hg.validFrom);
    );
}

TEST_F(TestPSQLHumanGeneralRepository, erase_strategy_test)
{
    insertHumanGeneral();

    ValueCriteria criteria (TypeName::getAttribute<HumanGeneral>("id"), "=", std::to_string(*hg.id));
    auto crepo = context.repositories->getHumanGeneralRepository();

    ASSERT_NO_THROW(crepo->erase(criteria));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from human.general "
                             "where human_id = $1 ", *hg.id);
    );

    ASSERT_EQ(res.size(), 1);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from human.general "
                        "where deleted = true and human_id = $1 "
                              "and blood_type = $2 "
                              "and gender = $3 "
                              "and race = $4 "
                              "and valid_from = to_timestamp($5)",
                        *hg.id, *hg.bloodType, *hg.gender, *hg.race,
                        *hg.validFrom);
    );
}

TEST_F(TestPSQLHumanGeneralRepository, get_test)
{
    insertHumanGeneral();
    std::shared_ptr<ITimeChangeableRepositorySet<HumanGeneral>> set = nullptr;;

    ASSERT_NO_THROW(set = repo->getAll());

    auto id_iter = set->begin(),
         id_end = set->end();

    ASSERT_NO_THROW(ASSERT_TRUE(id_end->notEqual(id_iter)));

    auto iter = set->beginId(id_iter),
         end = set->endId(id_iter);

    ASSERT_NO_THROW(ASSERT_TRUE(end->notEqual(iter)));

    ASSERT_TRUE(test_eq(hg, iter->get()));
    iter->next();
    ASSERT_NO_THROW(ASSERT_FALSE(end->notEqual(iter)));
    id_iter->next();
    ASSERT_NO_THROW(ASSERT_FALSE(id_end->notEqual(id_iter)));
}

#endif

