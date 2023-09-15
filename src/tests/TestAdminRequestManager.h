#ifndef _TESTADMINREQUESTMANAGER_H_
#define _TESTADMINREQUESTMANAGER_H_

#include <gtest/gtest.h>

#include "setupMockTest.h"
#include "UserInfoManager.h"
#include "AdminRequestManager.h"
#include "UserRequestManager.h"
#include "LoginManager.h"
#include "UserMapper.h"

#include "test_eq.h"

struct AdminRequestManagerTest : public testing::Test {
    std::shared_ptr<AppContext> context;
    std::string user_hash, admin_hash;
    const Human mergable = Human(1, "Name", "Surename", Place(), 0);
    const User user = User(1, "test", "12345", "test@mail.com");
    const User admin = User(2, "admin", "12345", "admin@mail.com");

    void SetUp()
    {
        context = setupRepositories();

        auto login = context->getLoginManager();
        login->registerUser(user);
        login->registerUser(admin);
        user_hash = login->login(user.email, user.password);
        admin_hash = login->login(admin.email, admin.password);

        context->getRepositoryContext().getUserRoleRepository()->create(UserRole(1, admin.id, "admin"));

        context->getRepositoryContext().getHumanRepository()->create(mergable);
    }
    void TearDown() {}
};

TEST_F(AdminRequestManagerTest, not_authenticated)
{
    auto manager = context->getAdminRequestManager();
    auto login = context->getLoginManager();

    login->exit(admin_hash);

    ASSERT_THROW(manager->getRequests(admin_hash), NotAuthenticatedAdminRequestManagerException);
    ASSERT_THROW(manager->updateRequest(admin_hash, MergeRequest()), NotAuthenticatedAdminRequestManagerException);
}

TEST_F(AdminRequestManagerTest, not_authorized)
{
    auto manager = context->getAdminRequestManager();

    ASSERT_THROW(manager->getRequests(user_hash), NotAuthorizedAdminRequestManagerException);
    ASSERT_THROW(manager->updateRequest(user_hash, MergeRequest()), NotAuthorizedAdminRequestManagerException);
}

MergeRequest setupRequest(const struct AdminRequestManagerTest *const str)
{
    auto umanager = str->context->getUserRequestManager();

    const UserMapper::Map req_map =
    {
        {"id", std::to_string(str->mergable.id)},
    };

    umanager->setHuman(str->user_hash, req_map);

    return MergeRequest (1, str->user, str->mergable, "new");
}

TEST_F(AdminRequestManagerTest, basic_get)
{
    const MergeRequest ref = setupRequest(this);
    auto manager = context->getAdminRequestManager();

    RequestSet set;
    ASSERT_NO_THROW(set = manager->getRequests(admin_hash));
    auto iter = set.begin();

    ASSERT_TRUE(set.end() != iter);
    ASSERT_TRUE(test_eq(*iter, ref));
    ASSERT_FALSE(set.end() != ++iter);
}

TEST_F(AdminRequestManagerTest, basic_approve)
{
    MergeRequest ref = setupRequest(this);
    auto manager = context->getAdminRequestManager();

    ref.state = "approved";
    ASSERT_NO_THROW(manager->updateRequest(admin_hash, ref));

    auto repo = context->getRepositoryContext().getMergeRequestRepository();
    auto set = repo->getAll();
    auto iter = set->begin(),
         end = set->end();

    ASSERT_TRUE(end->notEqual(iter));
    ASSERT_TRUE(test_eq(iter->get(), ref));
    iter->next();
    ASSERT_FALSE(end->notEqual(iter));

    auto uimanager = context->getUserInfoManager();
    ASSERT_TRUE(uimanager->isHuman(user_hash));
}

TEST_F(AdminRequestManagerTest, basic_decline)
{
    MergeRequest ref = setupRequest(this);
    auto manager = context->getAdminRequestManager();

    ref.state = "declined";
    ASSERT_NO_THROW(manager->updateRequest(admin_hash, ref));

    auto repo = context->getRepositoryContext().getMergeRequestRepository();
    auto set = repo->getAll();
    auto iter = set->begin(),
         end = set->end();

    ASSERT_TRUE(end->notEqual(iter));
    ASSERT_TRUE(test_eq(iter->get(), ref));
    iter->next();
    ASSERT_FALSE(end->notEqual(iter));

    auto uimanager = context->getUserInfoManager();

    ASSERT_FALSE(uimanager->isHuman(user_hash));
}

TEST_F(AdminRequestManagerTest, unspecified_state)
{
    MergeRequest ref = setupRequest(this);
    auto manager = context->getAdminRequestManager();

    ref.state = "random";
    ASSERT_THROW(manager->updateRequest(admin_hash, ref), NoHandlerAdminRequestManagerException);
}

#endif

