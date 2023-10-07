#ifndef _TESTPSQLUSERROLEREPOSITORY_H_
#define _TESTPSQLUSERROLEREPOSITORY_H_

#include <gtest/gtest.h>
#include "test_eq.h"

#include "typestring.h"

#include "setupPSQLTest.h"
#include "ValueCriteria.h"
#include "LogicCriteriaBuilder.h"

struct TestPSQLUserRoleRepository : public testing::Test {
    PSQLTestContext context;
    User user;

    void SetUp()
    {
        context = setupPSQLRepositories();
        pqxx::work w (*context.connection);
        pqxx::result r = w.exec("insert into authentication.users (email, password, name) "
                                            "values               ('new@mail.ru', '123', 'new') "
                                "returning id");
        w.commit();
        user = User(r[0][0].as<unsigned long long>(), "new", "123", "new@mail.ru");
    }
};

TEST_F(TestPSQLUserRoleRepository, create_test)
{
    UserRole role (0, user.id, "admin");

    auto urrepo = context.repositories->getUserRoleRepository();

    ASSERT_NO_THROW(urrepo->create(role));

    pqxx::nontransaction nt (*context.connection);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from authentication.user_roles "
                        "where user_id = $1 "
                              "and role = $2",
                        *role.userId, *role.role)
    );
}

TEST_F(TestPSQLUserRoleRepository, update_test)
{
    pqxx::work w (*context.connection);
    pqxx::result r = w.exec_params("insert into authentication.user_roles (user_id, role) "
                                               "values                    ($1, 'admin') "
                                   "returning id", *user.id);
    w.commit();
    UserRole role (r[0][0].as<unsigned long long>(), user.id, "user");

    auto urrepo = context.repositories->getUserRoleRepository();

    ASSERT_NO_THROW(urrepo->update(role));

    pqxx::nontransaction nt (*context.connection);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from authentication.user_roles "
                        "where id = $1 "
                              "and user_id = $2 "
                              "and role = $3",
                        *role.id, *role.userId, *role.role)
    );
}

TEST_F(TestPSQLUserRoleRepository, erase_single_test)
{
    pqxx::work w (*context.connection);
    pqxx::result r = w.exec_params("insert into authentication.user_roles (user_id, role) "
                                               "values                    ($1, 'admin') "
                                   "returning id", *user.id);
    w.commit();
    UserRole role (r[0][0].as<unsigned long long>(), user.id, "admin");

    auto urrepo = context.repositories->getUserRoleRepository();

    ASSERT_NO_THROW(urrepo->erase(role));

    pqxx::nontransaction nt (*context.connection);

    ASSERT_NO_THROW
    (
        r = nt.exec_params("select * from authentication.user_roles "
                           "where id = $1 "
                                 "and user_id = $2 "
                                 "and role = $3",
                           *role.id, *role.userId, *role.role)
    );

    ASSERT_EQ(r.size(), 0);
}

TEST_F(TestPSQLUserRoleRepository, erase_strategy_test)
{
    pqxx::work w (*context.connection);
    pqxx::result r = w.exec_params("insert into authentication.user_roles (user_id, role) "
                                               "values                    ($1, 'admin') "
                                   "returning id", *user.id);
    w.commit();

    LogicCriteriaBuilder builder (std::make_shared<ValueCriteria>(TypeName::getAttribute<UserRole>("id"), "=", r[0][0].as<std::string>()));
    builder.addAND(std::make_shared<ValueCriteria>(TypeName::getAttribute<UserRole>("userId"), "=", std::to_string(*user.id)));
    builder.addAND(std::make_shared<ValueCriteria>(TypeName::getAttribute<UserRole>("role"), "=", "admin"));

    auto urrepo = context.repositories->getUserRoleRepository();

    ASSERT_NO_THROW(urrepo->erase(*builder.get()));

    pqxx::nontransaction nt (*context.connection);

    ASSERT_NO_THROW
    (
        r = nt.exec_params("select * from authentication.user_roles "
                           "where id = $1 "
                                 "and user_id = $2 "
                                 "and role = $3",
                           r[0][0].as<std::string>(), *user.id, "admin")
    );

    ASSERT_EQ(r.size(), 0);
}

TEST_F(TestPSQLUserRoleRepository, get_test)
{
    pqxx::work w (*context.connection);
    pqxx::result r = w.exec_params("insert into authentication.user_roles (user_id, role) "
                                               "values                    ($1, 'admin') "
                                   "returning id", *user.id);
    w.commit();
    UserRole role (r[0][0].as<unsigned long long>(), user.id, "admin");

    auto urrepo = context.repositories->getUserRoleRepository();
    std::shared_ptr<IRepositorySet<UserRole>> set = nullptr;;

    ASSERT_NO_THROW(set = urrepo->getAll());

    auto iter = set->begin(),
         end = set->end();

    ASSERT_NO_THROW(ASSERT_TRUE(end->notEqual(iter)));
    ASSERT_TRUE(test_eq(role, iter->get()));
    iter->next();
    ASSERT_NO_THROW(ASSERT_FALSE(end->notEqual(iter)));
}

#endif

