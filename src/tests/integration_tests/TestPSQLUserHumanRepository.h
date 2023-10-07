#ifndef _TESTPSQLUSERHUMANREPOSITORY_H_
#define _TESTPSQLUSERHUMANREPOSITORY_H_

#include <gtest/gtest.h>
#include "test_eq.h"

#include "typestring.h"
#include "date_common.h"

#include "setupPSQLTest.h"
#include "ValueCriteria.h"
#include "LogicCriteriaBuilder.h"

struct TestPSQLUserHumanRepository : public testing::Test {
    PSQLTestContext context;
    User user;
    Human human;
    Place place;

    void SetUp()
    {
        std::time_t now = std::time(nullptr);
        context = setupPSQLRepositories();
        pqxx::work w (*context.connection);
        pqxx::result r = w.exec("insert into authentication.users (email, password, name) "
                                            "values               ('new@mail.ru', '123', 'new') "
                                "returning id");
        user = User(r[0][0].as<unsigned long long>(), "new", "123", "new@mail.ru");

        r = w.exec("insert into entities.place (source) values ('desktop') returning id");
        place = Place(r[0][0].as<unsigned long long>(), "type", "name", 123, "continent", now);
        w.exec_params("insert into place.general (place_id, type, name, area, continent, valid_from, source) "
                      "values ($1, $2, $3, $4, $5, $6, 'desktop')",
                      *place.id, *place.type, *place.name, *place.area,
                      *place.continent, DateCommon::getTime(*place.validFrom));



        r = w.exec("insert into entities.human (source) values ('desktop') returning id");
        human = Human(r[0][0].as<unsigned long long>(), "name", "surename",
                      place, now);
        w.exec_params("insert into human.names (human_id, first_name, last_name, valid_from, source) "
                      "values ($1, $2, $3, $4, 'desktop')",
                      *human.id, *human.firstName, *human.lastName, DateCommon::getTime(*human.validFrom));
        w.exec_params("insert into human.birth_place (human_id, place_id, source) "
                      "values ($1, $2, 'desktop')",
                      *human.id, *human.birthPlace->id);

        w.commit();
    }
};

TEST_F(TestPSQLUserHumanRepository, create_test)
{
    UserHuman uh (user.id, human);

    auto uhrepo = context.repositories->getUserHumanRepository();

    ASSERT_NO_THROW(uhrepo->create(uh));

    pqxx::nontransaction nt (*context.connection);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from authentication.user_human "
                        "where user_id = $1 "
                              "and human_id = $2",
                        *user.id, *human.id)
    );
}

TEST_F(TestPSQLUserHumanRepository, update_test)
{
    pqxx::work w (*context.connection);
    w.exec_params("insert into authentication.user_human (user_id, human_id) "
                  "values ($1, $2)", *user.id, *human.id);
    pqxx::result r = w.exec("insert into entities.human (source) values ('desktop') returning id");
    Human human (r[0][0].as<unsigned long long>(), "name", "surename",
                  place, std::time(nullptr));
    w.exec_params("insert into human.names (human_id, first_name, last_name, valid_from, source) "
                  "values ($1, $2, $3, $4, 'desktop')",
                  *human.id, *human.firstName, *human.lastName, DateCommon::getTime(*human.validFrom));
    w.exec_params("insert into human.birth_place (human_id, place_id, source) "
                  "values ($1, $2, 'desktop')",
                  *human.id, *human.birthPlace->id);
    w.commit();

    UserHuman uh (user.id, human);

    auto uhrepo = context.repositories->getUserHumanRepository();

    ASSERT_NO_THROW(uhrepo->update(uh));

    pqxx::nontransaction nt (*context.connection);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from authentication.user_human "
                        "where user_id = $1 "
                              "and human_id = $2",
                        *user.id, *human.id)
    );
}

TEST_F(TestPSQLUserHumanRepository, erase_single_test)
{
    pqxx::work w (*context.connection);
    w.exec_params("insert into authentication.user_human (user_id, human_id) "
                  "values ($1, $2)", *user.id, *human.id);
    w.commit();

    UserHuman uh (*user.id, human);

    auto uhrepo = context.repositories->getUserHumanRepository();

    ASSERT_NO_THROW(uhrepo->erase(uh));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from authentication.user_human "
                             "where user_id = $1 and human_id = $2",
                             *user.id, *human.id)
    );

    ASSERT_EQ(res.size(), 0);
}

TEST_F(TestPSQLUserHumanRepository, erase_strategy_test)
{
    pqxx::work w (*context.connection);
    w.exec_params("insert into authentication.user_human (user_id, human_id) "
                  "values ($1, $2)", *user.id, *human.id);
    w.commit();

    LogicCriteriaBuilder builder (std::make_shared<ValueCriteria>(TypeName::getAttribute<UserHuman>("id"), "=", std::to_string(*user.id)));
    builder.addAND(std::make_shared<ValueCriteria>(TypeName::getAttribute<UserHuman>("human.id"), "=", std::to_string(*human.id)));

    auto uhrepo = context.repositories->getUserHumanRepository();

    ASSERT_NO_THROW(uhrepo->erase(*builder.get()));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from authentication.user_human "
                             "where user_id = $1 and human_id = $2",
                             *user.id, *human.id)
    );

    ASSERT_EQ(res.size(), 0);
}

TEST_F(TestPSQLUserHumanRepository, get_test)
{
    pqxx::work w (*context.connection);
    w.exec_params("insert into authentication.user_human (user_id, human_id) "
                  "values ($1, $2)", *user.id, *human.id);
    w.commit();

    UserHuman uh (user.id, human);

    auto uhrepo = context.repositories->getUserHumanRepository();
    std::shared_ptr<IRepositorySet<UserHuman>> set = nullptr;;

    ASSERT_NO_THROW(set = uhrepo->getAll());

    auto iter = set->begin(),
         end = set->end();

    ASSERT_NO_THROW(ASSERT_TRUE(end->notEqual(iter)));
    ASSERT_TRUE(test_eq(uh, iter->get()));
    iter->next();
    ASSERT_NO_THROW(ASSERT_FALSE(end->notEqual(iter)));
}

#endif

