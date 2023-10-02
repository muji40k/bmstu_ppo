#ifndef _TESTPSQLUSERREPOSITORY_H_
#define _TESTPSQLUSERREPOSITORY_H_

#include <gtest/gtest.h>
#include "test_eq.h"

#include "typestring.h"

#include "setupPSQLTest.h"
#include "ValueCriteria.h"
#include "LogicCriteriaBuilder.h"

struct TestPSQLUserRepository : public testing::Test {
    PSQLTestContext context;

    void SetUp()
    {
        context = setupPSQLRepositories();
        pqxx::work w (*context.connection);
    }
};

TEST_F(TestPSQLUserRepository, create_test)
{
    User user (0, "new", "123", "new@gmail.com");

    auto urepo = context.repositories->getUserRepository();

    ASSERT_NO_THROW(urepo->create(user));

    pqxx::nontransaction nt (*context.connection);

    ASSERT_NO_THROW
    (
        nt.exec1("select * from authentication.users "
                 "where name='new' "
                       "and password='123'"
                       "and email='new@gmail.com'")
    );
}

TEST_F(TestPSQLUserRepository, update_test)
{
    pqxx::work w (*context.connection);
    pqxx::result r = w.exec("insert into authentication.users (email, password, name) "
                                        "values               ('new@mail.ru', '123', 'new') "
                            "returning id");
    w.commit();
    User user (r[0][0].as<unsigned long long>(), "update", "321", "update@gmail.com");

    auto urepo = context.repositories->getUserRepository();

    ASSERT_NO_THROW(urepo->update(user));

    pqxx::nontransaction nt (*context.connection);

    ASSERT_NO_THROW
    (
        nt.exec1("select * from authentication.users "
                 "where name='update' "
                       "and password='321'"
                       "and email='update@gmail.com'")
    );
}

TEST_F(TestPSQLUserRepository, erase_single_test)
{
    pqxx::work w (*context.connection);
    pqxx::result r = w.exec("insert into authentication.users (email, password, name) "
                                        "values               ('new@mail.ru', '123', 'new') "
                            "returning id");
    w.commit();
    User user (r[0][0].as<unsigned long long>(), "new", "123", "new@mail.ru");

    auto urepo = context.repositories->getUserRepository();

    ASSERT_NO_THROW(urepo->erase(user));

    pqxx::nontransaction nt (*context.connection);

    ASSERT_NO_THROW
    (
        r = nt.exec("select * from authentication.users "
                    "where name='new' "
                          "and password='123'"
                          "and email='new@mail.ru'")
    );

    ASSERT_EQ(r.size(), 0);
}

TEST_F(TestPSQLUserRepository, erase_strategy_test)
{
    pqxx::work w (*context.connection);
    pqxx::result r = w.exec("insert into authentication.users (email, password, name) "
                                        "values               ('new@mail.ru', '123', 'new') "
                            "returning id");
    w.commit();

    LogicCriteriaBuilder builder (std::make_shared<ValueCriteria>(TypeName::getAttribute<User>("email"), "=", "new@mail.ru"));
    builder.addAND(std::make_shared<ValueCriteria>(TypeName::getAttribute<User>("password"), "=", "123"));
    builder.addAND(std::make_shared<ValueCriteria>(TypeName::getAttribute<User>("name"), "=", "new"));

    auto urepo = context.repositories->getUserRepository();

    ASSERT_NO_THROW(urepo->erase(*builder.get()));

    pqxx::nontransaction nt (*context.connection);

    ASSERT_NO_THROW
    (
        r = nt.exec("select * from authentication.users "
                    "where name='new' "
                          "and password='123'"
                          "and email='new@mail.ru'")
    );

    ASSERT_EQ(r.size(), 0);
}

TEST_F(TestPSQLUserRepository, get_test)
{
    pqxx::work w (*context.connection);
    pqxx::result r = w.exec("insert into authentication.users (email, password, name) "
                                        "values               ('new@mail.ru', '123', 'new') "
                            "returning id");
    w.commit();
    User user (r[0][0].as<unsigned long long>(), "new", "123", "new@mail.ru");

    auto urepo = context.repositories->getUserRepository();
    std::shared_ptr<IRepositorySet<User>> set = nullptr;;

    ASSERT_NO_THROW(set = urepo->getAll());

    auto iter = set->begin(),
         end = set->end();

    ASSERT_NO_THROW(ASSERT_TRUE(end->notEqual(iter)));
    ASSERT_TRUE(test_eq(user, iter->get()));
    iter->next();
    ASSERT_NO_THROW(ASSERT_FALSE(end->notEqual(iter)));
}

#endif

