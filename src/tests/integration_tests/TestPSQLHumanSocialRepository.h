#ifndef _TESTPSQLHUMANSOCIALREPOSITORY_H_
#define _TESTPSQLHUMANSOCIALREPOSITORY_H_

#include <gtest/gtest.h>
#include "test_eq.h"

#include "typestring.h"
#include "date_common.h"

#include "setupPSQLTest.h"
#include "ValueCriteria.h"

struct TestPSQLHumanSocialRepository : public testing::Test {
    PSQLTestContext context;
    std::shared_ptr<IHumanSocialRepository> repo;
    HumanSocial hs;

    void insertHumanSocial(void)
    {
        pqxx::work w (*context.connection);
        w.exec_params("insert into human.social (human_id, religion, wealth, literacy, busyness, valid_from, source) "
                      "values ($1, $2, $3, $4, $5, $6, 'desktop')",
                      *hs.id, *hs.religion, *hs.wealth, *hs.literacy, *hs.busyness,
                      DateCommon::getTime(*hs.validFrom));
        w.commit();
    }

    void SetUp()
    {
        std::time_t now = std::time(nullptr);
        context = setupPSQLRepositories();
        repo = context.repositories->getHumanSocialRepository();
        pqxx::work w (*context.connection);

        pqxx::result r = w.exec("insert into entities.human (source) values ('desktop') returning id");
        hs = HumanSocial(r[0][0].as<unsigned long long>(), "religion", "wealth", "literacy", "busyness", now);
        w.commit();
    }
};

TEST_F(TestPSQLHumanSocialRepository, create_test)
{
    ASSERT_NO_THROW(repo->create(hs));

    pqxx::nontransaction nt (*context.connection);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from human.social "
                        "where human_id = $1 "
                              "and religion = $2 "
                              "and wealth = $3 "
                              "and literacy = $4 "
                              "and busyness = $5 "
                              "and valid_from = to_timestamp($6)",
                        *hs.id, *hs.religion, *hs.wealth, *hs.literacy, *hs.busyness,
                        *hs.validFrom);
    );
}

TEST_F(TestPSQLHumanSocialRepository, update_test)
{
    insertHumanSocial();
    HumanSocial updated (hs.id, "update", "update", "update", "update", std::time(nullptr));

    ASSERT_NO_THROW(repo->update(updated));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from human.social "
                             "where human_id = $1 ", *hs.id);
    );

    ASSERT_EQ(res.size(), 2);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from human.social "
                        "where human_id = $1 "
                              "and religion = $2 "
                              "and wealth = $3 "
                              "and literacy = $4 "
                              "and busyness = $5 "
                              "and valid_from = to_timestamp($6)",
                        *updated.id, *updated.religion, *updated.wealth, *updated.literacy, *updated.busyness,
                        *updated.validFrom);
    );
}

TEST_F(TestPSQLHumanSocialRepository, erase_single_test)
{
    insertHumanSocial();

    ASSERT_NO_THROW(repo->erase(hs));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from human.social "
                             "where human_id = $1 ", *hs.id);
    );

    ASSERT_EQ(res.size(), 1);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from human.social "
                        "where deleted = true and human_id = $1 "
                              "and religion = $2 "
                              "and wealth = $3 "
                              "and literacy = $4 "
                              "and busyness = $5 "
                              "and valid_from = to_timestamp($6)",
                        *hs.id, *hs.religion, *hs.wealth, *hs.literacy, *hs.busyness,
                        *hs.validFrom);
    );
}

TEST_F(TestPSQLHumanSocialRepository, erase_strategy_test)
{
    insertHumanSocial();

    ValueCriteria criteria (TypeName::getAttribute<HumanSocial>("id"), "=", std::to_string(*hs.id));
    auto crepo = context.repositories->getHumanSocialRepository();

    ASSERT_NO_THROW(crepo->erase(criteria));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from human.social "
                             "where human_id = $1 ", *hs.id);
    );

    ASSERT_EQ(res.size(), 1);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from human.social "
                        "where deleted = true and human_id = $1 "
                              "and religion = $2 "
                              "and wealth = $3 "
                              "and literacy = $4 "
                              "and busyness = $5 "
                              "and valid_from = to_timestamp($6)",
                        *hs.id, *hs.religion, *hs.wealth, *hs.literacy, *hs.busyness,
                        *hs.validFrom);
    );
}

TEST_F(TestPSQLHumanSocialRepository, get_test)
{
    insertHumanSocial();
    std::shared_ptr<ITimeChangeableRepositorySet<HumanSocial>> set = nullptr;;

    ASSERT_NO_THROW(set = repo->getAll());

    auto id_iter = set->begin(),
         id_end = set->end();

    ASSERT_NO_THROW(ASSERT_TRUE(id_end->notEqual(id_iter)));

    auto iter = set->beginId(id_iter),
         end = set->endId(id_iter);

    ASSERT_NO_THROW(ASSERT_TRUE(end->notEqual(iter)));

    ASSERT_TRUE(test_eq(hs, iter->get()));
    iter->next();
    ASSERT_NO_THROW(ASSERT_FALSE(end->notEqual(iter)));
    id_iter->next();
    ASSERT_NO_THROW(ASSERT_FALSE(id_end->notEqual(id_iter)));
}

#endif

