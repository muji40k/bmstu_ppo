#ifndef _TESTUSERREQUESTMANAGER_H_
#define _TESTUSERREQUESTMANAGER_H_

#include <gtest/gtest.h>
#include <algorithm>

#include "typestring.h"

#include "setupMockTest.h"
#include "UserRequestManager.h"
#include "LoginManager.h"
#include "UserMapper.h"

#include "test_eq.h"

struct UserRequestManagerTest : public testing::Test {
    std::shared_ptr<AppContext> context;
    const Human ref_human_a = Human(1, "NameA", "Surename", Place(), 0);
    const Human ref_human_b = Human(2, "NameB", "Surename", Place(), 0);
    std::string hash;
    const User user = User(1, "test", "12345", "test@mail.com");

    void SetUp()
    {
        context = setupRepositories();

        auto login = context->getLoginManager();
        login->registerUser(user);
        hash = login->login(user.email, user.password);

        auto repo = context->getRepositoryContext().getHumanRepository();
        repo->create(ref_human_a);
        repo->create(ref_human_b);
    }
    void TearDown() {}
};

TEST_F(UserRequestManagerTest, not_authenticated)
{
    auto manager = context->getUserRequestManager();
    auto login = context->getLoginManager();

    login->exit(hash);
    const UserMapper::Map ref_map = {{"id", "1"}};

    ASSERT_THROW(manager->findHuman(hash, ref_map), NotAuthenticatedUserRequestManagerException);
    ASSERT_THROW(manager->setHuman(hash, ref_map), NotAuthenticatedUserRequestManagerException);
}

TEST_F(UserRequestManagerTest, basic_find)
{
    auto manager = context->getUserRequestManager();

    const UserMapper::Map req_map =
    {
        {"first_name", ref_human_a.firstName},
        {"last_name", ref_human_a.lastName}
    };

    const std::list<UserMapper::Map> ref =
    {
        {
            {"id", std::to_string(ref_human_a.id)},
            {"first_name", ref_human_a.firstName},
            {"last_name", ref_human_a.lastName},
            {"birth_place", "none"},
        }
    };

    ASSERT_NO_THROW(ASSERT_EQ(manager->findHuman(hash, req_map), ref));
}

TEST_F(UserRequestManagerTest, basic_find_intersection)
{
    auto manager = context->getUserRequestManager();

    const UserMapper::Map req_map =
    {
        {"last_name", ref_human_a.lastName},
    };

    const std::list<UserMapper::Map> ref =
    {
        {
            {"id", std::to_string(ref_human_a.id)},
            {"first_name", ref_human_a.firstName},
            {"last_name", ref_human_a.lastName},
            {"birth_place", "none"},
        },
        {
            {"id", std::to_string(ref_human_b.id)},
            {"first_name", ref_human_b.firstName},
            {"last_name", ref_human_b.lastName},
            {"birth_place", "none"},
        }
    };
    std::list<UserMapper::Map> res, diff;

    ASSERT_NO_THROW(res = manager->findHuman(hash, req_map));

    std::set_difference(ref.begin(), ref.end(),
                        res.begin(), res.end(),
                        std::back_inserter(diff),
                        [](auto& a, auto& b) { return a == b;});

    ASSERT_TRUE(diff.empty());
}

TEST_F(UserRequestManagerTest, empty_find)
{
    auto manager = context->getUserRequestManager();

    const UserMapper::Map req_map;

    ASSERT_THROW(manager->findHuman(hash, req_map), EmptyDataUserRequestManagerException);
}

TEST_F(UserRequestManagerTest, unsuitable_find)
{
    auto manager = context->getUserRequestManager();

    const UserMapper::Map req_map =
    {
        {"id", std::to_string(ref_human_b.id)},
        {"first_name", ref_human_a.firstName},
        {"last_name", ref_human_a.lastName}
    };

    ASSERT_THROW(manager->findHuman(hash, req_map), UnspecifiedDataUserRequestManagerException);
}

TEST_F(UserRequestManagerTest, basic_set)
{
    auto manager = context->getUserRequestManager();

    const MergeRequest ref_mr (1, user, ref_human_a, "new");

    const UserMapper::Map req_map =
    {
        {"id", std::to_string(ref_human_a.id)},
    };

    ASSERT_NO_THROW(manager->setHuman(hash, req_map));

    auto repo = context->getRepositoryContext().getMergeRequestRepository();

    auto set = repo->getAll();
    auto iter = set->begin(),
         end = set->end();

    ASSERT_TRUE(end->notEqual(iter));
    ASSERT_TRUE(test_eq(iter->get(), ref_mr));
}

TEST_F(UserRequestManagerTest, empty_set)
{
    auto manager = context->getUserRequestManager();

    const UserMapper::Map req_map;

    ASSERT_THROW(manager->setHuman(hash, req_map), EmptyDataUserRequestManagerException);
}

TEST_F(UserRequestManagerTest, unsuitable_set)
{
    auto manager = context->getUserRequestManager();

    const UserMapper::Map req_map =
    {
        {"first_name", ref_human_a.firstName},
        {"last_name", ref_human_a.lastName}
    };

    ASSERT_THROW(manager->setHuman(hash, req_map), UnsuitableDataUserRequestManagerException);
}

TEST_F(UserRequestManagerTest, not_found_set)
{
    auto manager = context->getUserRequestManager();

    const UserMapper::Map req_map =
    {
        {"id", "100000000"},
    };

    ASSERT_THROW(manager->setHuman(hash, req_map), NotFoundUserRequestManagerException);
}

#endif

