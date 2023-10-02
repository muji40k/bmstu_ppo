#ifndef _TESTLOGINMANAGER_H_
#define _TESTLOGINMANAGER_H_

#include <gtest/gtest.h>

#include "setupMockTest.h"
#include "LoginManager.h"
#include "MD5LoginManager.h"
#include "test_eq.h"

struct LoginManagerTest : public testing::Test {
    std::shared_ptr<AppContext> context;

    void SetUp() { context = setupRepositories(); }
    void TearDown() {}
};

TEST_F(LoginManagerTest, registration)
{
    const User ref_user(1, "test", "12345", "test@mail.com");
    User user;
    auto manager = context->getLoginManager();
    std::string ref_hash = MD5LoginManager::hash(ref_user), hash;

    ASSERT_NO_THROW(manager->registerUser(ref_user));

    ASSERT_NO_THROW(hash = manager->login(ref_user.email, ref_user.password));
    ASSERT_EQ(ref_hash, hash);

    ASSERT_NO_THROW(user = manager->getAuthenticated(hash));
    ASSERT_TRUE(test_eq(user, ref_user));
}

TEST_F(LoginManagerTest, double_registration)
{
    const User ref_user(1, "test", "12345", "test@mail.com");
    auto manager = context->getLoginManager();

    ASSERT_NO_THROW(manager->registerUser(ref_user));
    ASSERT_THROW(manager->registerUser(ref_user), AlreadyRegisteredException);
}

TEST_F(LoginManagerTest, same_email_registration)
{
    const User ref_user1(1, "test", "12345", "test@mail.com");
    const User ref_user2(2, "another", "abcd", "test@mail.com");
    auto manager = context->getLoginManager();

    ASSERT_NO_THROW(manager->registerUser(ref_user1));
    ASSERT_THROW(manager->registerUser(ref_user2), AlreadyRegisteredException);
}

TEST_F(LoginManagerTest, wrong_login_password)
{
    const User ref_user(1, "test", "12345", "test@mail.com");
    auto manager = context->getLoginManager();

    ASSERT_NO_THROW(manager->registerUser(ref_user));

    ASSERT_THROW(manager->login(ref_user.email, "wrong_password"), WrongLoginException);
}

TEST_F(LoginManagerTest, wrong_login_email)
{
    const User ref_user(1, "test", "12345", "test@mail.com");
    auto manager = context->getLoginManager();

    ASSERT_NO_THROW(manager->registerUser(ref_user));

    ASSERT_THROW(manager->login("somewrong@mail.ru", ref_user.password), WrongLoginException);
}

TEST_F(LoginManagerTest, double_login)
{
    const User ref_user(1, "test", "12345", "test@mail.com");
    auto manager = context->getLoginManager();

    ASSERT_NO_THROW(manager->registerUser(ref_user));

    std::string hash;
    ASSERT_NO_THROW(hash = manager->login(ref_user.email, ref_user.password));

    ASSERT_THROW(manager->login(ref_user.email, ref_user.password), AlreadyLoggedinException);
}

TEST_F(LoginManagerTest, exit)
{
    const User ref_user(1, "test", "12345", "test@mail.com");
    auto manager = context->getLoginManager();
    std::string hash;

    ASSERT_NO_THROW(manager->registerUser(ref_user));
    ASSERT_NO_THROW(hash = manager->login(ref_user.email, ref_user.password));
    ASSERT_EQ(manager->isAuthenticated(hash), true);
    ASSERT_NO_THROW(manager->exit(hash));
    ASSERT_EQ(manager->isAuthenticated(hash), false);
}

TEST_F(LoginManagerTest, access_not_authenticated)
{
    const User ref_user(1, "test", "12345", "test@mail.com");
    auto manager = context->getLoginManager();
    std::string hash = MD5LoginManager::hash(ref_user);

    ASSERT_NO_THROW(manager->registerUser(ref_user));
    ASSERT_EQ(manager->isAuthenticated(hash), false);
    ASSERT_THROW(manager->getAuthenticated(hash), NotAuthenticatedException);
}

TEST_F(LoginManagerTest, update)
{
    const User ref_user(1, "test", "12345", "test@mail.com");
    const User updated_user(1, "chel", "54321", "test@mail.com");
    auto manager = context->getLoginManager();
    auto repo = context->getRepositoryContext().getUserRepository();
    const std::string ref_hash = MD5LoginManager::hash(ref_user),
                      updated_hash = MD5LoginManager::hash(updated_user);
    std::string hash;

    ASSERT_NO_THROW(manager->registerUser(ref_user));
    ASSERT_NO_THROW(hash = manager->login(ref_user.email, ref_user.password));
    ASSERT_EQ(hash, ref_hash);
    ASSERT_NO_THROW(ASSERT_TRUE(test_eq(manager->getAuthenticated(hash), ref_user)));

    ASSERT_NO_THROW(repo->update(updated_user));
    ASSERT_NO_THROW(hash = manager->update(hash));
    ASSERT_EQ(hash, updated_hash);
    ASSERT_NO_THROW(ASSERT_TRUE(test_eq(manager->getAuthenticated(hash), updated_user)));
}

TEST_F(LoginManagerTest, user_deleted)
{
    const User ref_user(1, "test", "12345", "test@mail.com");
    auto manager = context->getLoginManager();
    auto repo = context->getRepositoryContext().getUserRepository();
    std::string hash;

    ASSERT_NO_THROW(manager->registerUser(ref_user));
    ASSERT_NO_THROW(hash = manager->login(ref_user.email, ref_user.password));
    repo->erase(ref_user);
    ASSERT_THROW(manager->update(hash), NoUserException);
}

#endif

