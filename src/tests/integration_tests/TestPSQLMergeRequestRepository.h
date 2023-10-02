#ifndef _TESTPSQLMERGEREQUESTREPOSITORY_H_
#define _TESTPSQLMERGEREQUESTREPOSITORY_H_

#include <gtest/gtest.h>
#include "test_eq.h"

#include "typestring.h"
#include "date_common.h"

#include "setupPSQLTest.h"
#include "ValueCriteria.h"
#include "LogicCriteriaBuilder.h"

struct TestPSQLMergeRequestRepository : public testing::Test {
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

TEST_F(TestPSQLMergeRequestRepository, create_test)
{
    MergeRequest mr (0, user, human, "new");

    auto uhrepo = context.repositories->getMergeRequestRepository();

    ASSERT_NO_THROW(uhrepo->create(mr));

    pqxx::nontransaction nt (*context.connection);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from authentication.merge_requests "
                        "where user_id = $1 "
                              "and human_id = $2 "
                              "and state = $3",
                        *user.id, *human.id, *mr.state)
    );
}

TEST_F(TestPSQLMergeRequestRepository, update_test)
{
    pqxx::work w (*context.connection);
    pqxx::result r = w.exec_params("insert into authentication.merge_requests (user_id, human_id, state) "
                                               "values                        ($1, $2, 'new') "
                                   "returning id", *user.id, *human.id);
    w.commit();

    MergeRequest uh (r[0][0].as<unsigned long long>(), user, human, "accept");

    auto uhrepo = context.repositories->getMergeRequestRepository();

    ASSERT_NO_THROW(uhrepo->update(uh));

    pqxx::nontransaction nt (*context.connection);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from authentication.merge_requests "
                        "where user_id = $1 "
                              "and human_id = $2 "
                              "and state = $3",
                        *user.id, *human.id, "accept")
    );
}

TEST_F(TestPSQLMergeRequestRepository, erase_single_test)
{
    pqxx::work w (*context.connection);
    pqxx::result r = w.exec_params("insert into authentication.merge_requests (user_id, human_id, state) "
                                               "values                        ($1, $2, 'new') "
                                   "returning id", *user.id, *human.id);
    w.commit();

    MergeRequest uh (r[0][0].as<unsigned long long>(), user, human, "new");

    auto uhrepo = context.repositories->getMergeRequestRepository();

    ASSERT_NO_THROW(uhrepo->erase(uh));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from authentication.merge_requests "
                             "where user_id = $1 "
                                   "and human_id = $2 "
                                   "and state = $3",
                             *user.id, *human.id, "new")
    );

    ASSERT_EQ(res.size(), 0);
}

TEST_F(TestPSQLMergeRequestRepository, erase_strategy_test)
{
    pqxx::work w (*context.connection);
    pqxx::result r = w.exec_params("insert into authentication.merge_requests (user_id, human_id, state) "
                                               "values                        ($1, $2, 'new') "
                                   "returning id", *user.id, *human.id);
    w.commit();

    LogicCriteriaBuilder builder (std::make_shared<ValueCriteria>(TypeName::getAttribute<MergeRequest>("id"), "=", r[0][0].as<std::string>()));
    builder.addAND(std::make_shared<ValueCriteria>(TypeName::getAttribute<MergeRequest>("user.id"), "=", std::to_string(*user.id)));
    builder.addAND(std::make_shared<ValueCriteria>(TypeName::getAttribute<MergeRequest>("human.id"), "=", std::to_string(*human.id)));
    builder.addAND(std::make_shared<ValueCriteria>(TypeName::getAttribute<MergeRequest>("state"), "=", "new"));

    auto uhrepo = context.repositories->getMergeRequestRepository();

    ASSERT_NO_THROW(uhrepo->erase(*builder.get()));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from authentication.merge_requests "
                             "where user_id = $1 "
                                   "and human_id = $2 "
                                   "and state = $3",
                             *user.id, *human.id, "new")
    );

    ASSERT_EQ(res.size(), 0);
}

TEST_F(TestPSQLMergeRequestRepository, get_test)
{
    pqxx::work w (*context.connection);
    pqxx::result r = w.exec_params("insert into authentication.merge_requests (user_id, human_id, state) "
                                               "values                        ($1, $2, 'new') "
                                   "returning id", *user.id, *human.id);
    w.commit();

    MergeRequest uh (r[0][0].as<unsigned long long>(), user, human, "new");

    auto uhrepo = context.repositories->getMergeRequestRepository();
    std::shared_ptr<IRepositorySet<MergeRequest>> set = nullptr;;

    ASSERT_NO_THROW(set = uhrepo->getAll());

    auto iter = set->begin(),
         end = set->end();

    ASSERT_NO_THROW(ASSERT_TRUE(end->notEqual(iter)));
    ASSERT_TRUE(test_eq(uh, iter->get()));
    iter->next();
    ASSERT_NO_THROW(ASSERT_FALSE(end->notEqual(iter)));
}

#endif

