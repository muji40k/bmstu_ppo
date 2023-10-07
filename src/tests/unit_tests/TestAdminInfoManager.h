#ifndef _TESTADMININFOMANAGER_H_
#define _TESTADMININFOMANAGER_H_

#include <gtest/gtest.h>

#include "setupMockTest.h"
#include "AdminInfoManager.h"
#include "HumanAdminInfoStrategies.h"
#include "LoginManager.h"
#include "test_eq.h"

struct AdminInfoManagerTest : public testing::Test {
    std::shared_ptr<AppContext> context;
    std::string user_hash, admin_hash;
    const User user = User(1, "test", "12345", "test@mail.com");
    const User admin = User(2, "admin", "12345", "admin@mail.com");
    const Human human = Human(1, "Name", "Surename", Place(), 0);

    void SetUp()
    {
        context = setupRepositories();

        auto login = context->getLoginManager();
        login->registerUser(user);
        login->registerUser(admin);
        user_hash = login->login(user.email, user.password);
        admin_hash = login->login(admin.email, admin.password);

        context->getRepositoryContext().getUserRoleRepository()->create(UserRole(1, admin.id, "admin"));
    }
    void TearDown() {}
};

TEST_F(AdminInfoManagerTest, not_authenticated)
{
    auto manager = context->getAdminInfoManager();
    auto login = context->getLoginManager();

    login->exit(admin_hash);
    HumanGetAdminInfoStrategy strategy;

    ASSERT_THROW(manager->process(admin_hash, strategy), NotAuthenticatedAdminInfoManagerException);
}

TEST_F(AdminInfoManagerTest, not_authorized)
{
    auto manager = context->getAdminInfoManager();
    HumanGetAdminInfoStrategy strategy;

    ASSERT_THROW(manager->process(user_hash, strategy), NotAuthorizedAdminInfoManagerException);
}

void check_get(GetStrategyResult<std::shared_ptr<ITimeChangeableRepositorySet<Human>>> &get,
               const Human &ref)
{
    auto set = get.result();
    auto id_iter = set->begin(),
         id_end  = set->end();

    ASSERT_TRUE(id_end->notEqual(id_iter));

    auto iter = set->beginId(id_iter),
         end  = set->endId(id_iter);

    ASSERT_TRUE(end->notEqual(iter));
    ASSERT_TRUE(test_eq(iter->get(), ref));
    iter->next();
    ASSERT_FALSE(end->notEqual(iter));
    id_iter->next();
    ASSERT_FALSE(id_end->notEqual(id_iter));
}

TEST_F(AdminInfoManagerTest, crud_sequence)
{
    auto hrepo = context->getRepositoryContext().getHumanRepository();
    auto manager = context->getAdminInfoManager();
    Human updated (1, "Update", "New", Place(), 0);

    HumanCreateAdminInfoStrategy create (human);
    ASSERT_NO_THROW(manager->process(admin_hash, create));

    HumanGetAdminInfoStrategy get;
    ASSERT_NO_THROW(manager->process(admin_hash, get));
    check_get(get, human);

    HumanUpdateAdminInfoStrategy update (updated);
    ASSERT_NO_THROW(manager->process(admin_hash, update));
    HumanGetAdminInfoStrategy get2;
    ASSERT_NO_THROW(manager->process(admin_hash, get2));
    check_get(get2, updated);

    HumanEraseSingleAdminInfoStrategy erase (updated);
    ASSERT_NO_THROW(manager->process(admin_hash, erase));
    HumanGetAdminInfoStrategy get3;
    ASSERT_NO_THROW(manager->process(admin_hash, get3));

    auto set = get3.result();
    ASSERT_FALSE(set->end()->notEqual(set->begin()));
}

#endif

