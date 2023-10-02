#ifndef _TESTPSQLHUMANREPOSITORY_H_
#define _TESTPSQLHUMANREPOSITORY_H_

#include <gtest/gtest.h>
#include "test_eq.h"

#include "typestring.h"
#include "date_common.h"

#include "setupPSQLTest.h"
#include "ValueCriteria.h"

struct TestPSQLHumanRepository : public testing::Test {
    PSQLTestContext context;
    std::shared_ptr<IHumanRepository> repo;
    Human human;

    void insertHuman(void)
    {
        pqxx::work w (*context.connection);
        w.exec_params("insert into human.names (human_id, first_name, last_name, patronymic, valid_from, source) "
                      "values ($1, $2, $3, $4, $5, 'desktop')",
                      *human.id, *human.firstName, *human.lastName, *human.patronymic,
                      DateCommon::getTime(*human.validFrom));
        w.exec_params("insert into human.birth_place (human_id, place_id, source) "
                      "values ($1, $2, 'desktop')",
                      *human.id, *human.birthPlace->id);
        const Place &place = human.birthPlace;
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
        repo = context.repositories->getHumanRepository();
        pqxx::work w (*context.connection);

        pqxx::result r = w.exec("insert into entities.place (source) values ('desktop') returning id");
        Place place (r[0][0].as<unsigned long long>(), "type", "name", 123, "continent", now);

        r = w.exec("insert into entities.human (source) values ('desktop') returning id");
        human = Human(r[0][0].as<unsigned long long>(), "first_name", "last_name", "patronymic", place, now);
        w.commit();
    }
};

TEST_F(TestPSQLHumanRepository, create_test)
{
    ASSERT_NO_THROW(repo->create(human));

    pqxx::nontransaction nt (*context.connection);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from human.names "
                        "where human_id = $1 "
                              "and first_name = $2 "
                              "and last_name = $3 "
                              "and patronymic = $4 "
                              "and valid_from = to_timestamp($5)",
                        *human.id, *human.firstName, *human.lastName, *human.patronymic,
                        *human.validFrom);
    );

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from human.birth_place "
                        "where human_id = $1 "
                              "and place_id = $2",
                        *human.id, *human.birthPlace->id);
    );
}

TEST_F(TestPSQLHumanRepository, update_test)
{
    insertHuman();
    Human updated (human.id, "update", "update", "update", human.birthPlace, std::time(nullptr));

    ASSERT_NO_THROW(repo->update(updated));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from human.names "
                             "where human_id = $1 ", *human.id);
    );

    ASSERT_EQ(res.size(), 2);

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from human.birth_place "
                             "where human_id = $1 ", *human.id);
    );

    ASSERT_EQ(res.size(), 2);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from human.names "
                        "where human_id = $1 "
                              "and first_name = $2 "
                              "and last_name = $3 "
                              "and patronymic = $4 "
                              "and valid_from = to_timestamp($5)",
                        *updated.id, *updated.firstName, *updated.lastName, *updated.patronymic,
                        *updated.validFrom);
    );

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from human.birth_place "
                             "where human_id = $1 "
                                   "and place_id = $2",
                             *updated.id, *updated.birthPlace->id);
    );

    ASSERT_EQ(res.size(), 2);
}

TEST_F(TestPSQLHumanRepository, erase_single_test)
{
    insertHuman();

    ASSERT_NO_THROW(repo->erase(human));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from human.names "
                             "where human_id = $1 ", *human.id);
    );

    ASSERT_EQ(res.size(), 1);

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from human.birth_place "
                             "where human_id = $1 ", *human.id);
    );

    ASSERT_EQ(res.size(), 1);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from human.names "
                        "where deleted = true and human_id = $1 "
                              "and first_name = $2 "
                              "and last_name = $3 "
                              "and patronymic = $4 "
                              "and valid_from = to_timestamp($5)",
                        *human.id, *human.firstName, *human.lastName, *human.patronymic,
                        *human.validFrom);
    );

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from human.birth_place "
                        "where human_id = $1 "
                              "and place_id = $2",
                        *human.id, *human.birthPlace->id);
    );
}

TEST_F(TestPSQLHumanRepository, erase_strategy_test)
{
    insertHuman();

    ValueCriteria criteria (TypeName::getAttribute<Human>("id"), "=", std::to_string(*human.id));
    auto crepo = context.repositories->getHumanRepository();

    ASSERT_NO_THROW(crepo->erase(criteria));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from human.names "
                             "where human_id = $1 ", *human.id);
    );

    ASSERT_EQ(res.size(), 1);

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from human.birth_place "
                             "where human_id = $1 ", *human.id);
    );

    ASSERT_EQ(res.size(), 1);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from human.names "
                        "where deleted = true and human_id = $1 "
                              "and first_name = $2 "
                              "and last_name = $3 "
                              "and patronymic = $4 "
                              "and valid_from = to_timestamp($5)",
                        *human.id, *human.firstName, *human.lastName, *human.patronymic,
                        *human.validFrom);
    );

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from human.birth_place "
                        "where human_id = $1 "
                              "and place_id = $2",
                        *human.id, *human.birthPlace->id);
    );
}

TEST_F(TestPSQLHumanRepository, get_test)
{
    insertHuman();
    std::shared_ptr<ITimeChangeableRepositorySet<Human>> set = nullptr;;

    ASSERT_NO_THROW(set = repo->getAll());

    auto id_iter = set->begin(),
         id_end = set->end();

    ASSERT_NO_THROW(ASSERT_TRUE(id_end->notEqual(id_iter)));

    auto iter = set->beginId(id_iter),
         end = set->endId(id_iter);

    ASSERT_NO_THROW(ASSERT_TRUE(end->notEqual(iter)));

    ASSERT_TRUE(test_eq(human, iter->get()));
    iter->next();
    ASSERT_NO_THROW(ASSERT_FALSE(end->notEqual(iter)));
    id_iter->next();
    ASSERT_NO_THROW(ASSERT_FALSE(id_end->notEqual(id_iter)));
}

#endif

