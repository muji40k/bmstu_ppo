#ifndef _TESTAUTHORIZATIONMANAGER_H_
#define _TESTAUTHORIZATIONMANAGER_H_

#include <gtest/gtest.h>

#include "setupMockTest.h"
#include "AuthorizationManager.h"
#include "LoginManager.h"

struct AuthorizationManagerTest : public testing::Test {
    std::shared_ptr<AppContext> context;
    const User user  = User(1, "test", "12345", "test@mail.com");
    std::string hash;

    void SetUp()
    {
        context = setupRepositories();
        auto login = context->getLoginManager();
        login->registerUser(user);
        hash = login->login(user.email, user.password);
        auto repo = context->getRepositoryContext().getUserRoleRepository();
        repo->create(UserRole(1, user.id, "user"));
        repo->create(UserRole(2, user.id, "admin"));
    }
    void TearDown() {}
};

TEST_F(AuthorizationManagerTest, basic_granted_role_check)
{
    auto manager = context->getAuthorizationManager();
    ASSERT_NO_THROW(ASSERT_EQ(manager->authorize(hash, {"admin"}), true));
}

TEST_F(AuthorizationManagerTest, basic_revoked_role_check)
{
    auto manager = context->getAuthorizationManager();
    ASSERT_NO_THROW(ASSERT_EQ(manager->authorize(hash, {"supeuser"}), false));
}

TEST_F(AuthorizationManagerTest, empty_list)
{
    auto manager = context->getAuthorizationManager();
    ASSERT_THROW(manager->authorize(hash, {}), EmptyListException);
}

TEST_F(AuthorizationManagerTest, composition_test_all)
{
    auto manager = context->getAuthorizationManager();
    ASSERT_NO_THROW(ASSERT_EQ(manager->authorize(hash, {"admin", "user"}), true));
}

TEST_F(AuthorizationManagerTest, composition_test_one)
{
    auto manager = context->getAuthorizationManager();
    ASSERT_NO_THROW(ASSERT_EQ(manager->authorize(hash, {"admin", "superuser"}), true));
}

TEST_F(AuthorizationManagerTest, composition_test_none)
{
    auto manager = context->getAuthorizationManager();
    ASSERT_NO_THROW(ASSERT_EQ(manager->authorize(hash, {"tester", "superuser"}), false));
}

#endif

