#ifndef _TESTUSERINFOMANAGER_H_
#define _TESTUSERINFOMANAGER_H_

#include <gtest/gtest.h>

#include "setupMockTest.h"
#include "UserInfoManager.h"
#include "LoginManager.h"
#include "UserMapper.h"
#include "test_eq.h"

struct UserInfoManagerTest : public testing::Test {
    std::shared_ptr<AppContext> context;
    const Human ref_human = Human(1, "Name", "Surename", Place(), 0);
    std::string hash_no_human;
    std::string hash_human;
    const User user = User(1, "test", "12345", "test@mail.com");
    const User user_human_set = User(2, "test", "12345", "test2@mail.com");

    void SetUp()
    {
        context = setupRepositories();

        auto login = context->getLoginManager();
        login->registerUser(user);
        hash_no_human = login->login(user.email, user.password);

        login->registerUser(user_human_set);
        hash_human = login->login(user_human_set.email, user_human_set.password);

        auto repo = context->getRepositoryContext().getUserHumanRepository();
        repo->update(UserHuman(2, ref_human));
    }
    void TearDown() {}
};

TEST_F(UserInfoManagerTest, basic_info_get)
{
    auto manager = context->getUserInfoManager();

    const UserMapper::Map ref_map =
    {
        {"email", user.email},
        {"name", user.name}
    };

    ASSERT_NO_THROW(ASSERT_EQ(manager->getInfo(hash_no_human), ref_map));
}

TEST_F(UserInfoManagerTest, info_update)
{
    auto manager = context->getUserInfoManager();
    auto login = context->getLoginManager();

    const User updated (1, user.name, "password", "another@mail.ru");
    const UserMapper::Map ref_map =
    {
        {"email", updated.email},
        {"password", updated.password}
    };
    const UserMapper::Map ref_map_res =
    {
        {"email", updated.email},
        {"name", updated.name}
    };

    ASSERT_NO_THROW(manager->updateInfo(hash_no_human, ref_map));
    ASSERT_NO_THROW(hash_no_human = login->update(hash_no_human));
    ASSERT_NO_THROW(ASSERT_EQ(manager->getInfo(hash_no_human), ref_map_res));
    ASSERT_NO_THROW(ASSERT_TRUE(test_eq(login->getAuthenticated(hash_no_human), updated)));
}

TEST_F(UserInfoManagerTest, info_update_unspecified_item)
{
    auto manager = context->getUserInfoManager();
    const UserMapper::Map ref_map = {{"random", "item"}};
    ASSERT_THROW(manager->updateInfo(hash_no_human, ref_map), UnexpectedKeyUserInfoManagerException);
}

TEST_F(UserInfoManagerTest, not_authenticated)
{
    auto manager = context->getUserInfoManager();
    auto login = context->getLoginManager();

    login->exit(hash_no_human);
    const UserMapper::Map ref_map;

    ASSERT_THROW(manager->getInfo(hash_no_human), NotAuthenticatedUserInfoManagerException);
    ASSERT_THROW(manager->updateInfo(hash_no_human, ref_map), NotAuthenticatedUserInfoManagerException);
    ASSERT_THROW(manager->isHuman(hash_no_human), NotAuthenticatedUserInfoManagerException);
    ASSERT_THROW(manager->getHuman(hash_no_human), NotAuthenticatedUserInfoManagerException);
}

TEST_F(UserInfoManagerTest, no_human_set)
{
    auto manager = context->getUserInfoManager();

    ASSERT_NO_THROW(ASSERT_EQ(manager->isHuman(hash_no_human), false));
    ASSERT_THROW(manager->getHuman(hash_no_human), NotHumanUserInfoManagerException);
}

TEST_F(UserInfoManagerTest, human_set)
{
    auto manager = context->getUserInfoManager();

    const UserMapper::Map ref_map
    {
        {"first_name", ref_human.firstName},
        {"last_name", ref_human.lastName},
        {"birth_place", ref_human.birthPlace->name}
    };

    ASSERT_NO_THROW(ASSERT_EQ(manager->isHuman(hash_human), true));
    ASSERT_NO_THROW(ASSERT_EQ(manager->getHuman(hash_human), ref_map));
}

TEST_F(UserInfoManagerTest, human_set_all_getters)
{
    Place bplace (1, "city", "TestCity", 1234, "Eurasia", 0),
          cplace (2, "village", "TestVillage", 31, "Eurasia", 0);

    Human human (2, "Name2", "Surename2", bplace, 0);
    HumanAddress ha (2, cplace, 0);
    HumanLivingDates hld (2, 0, 0);
    HumanSocial hs (2, "TestReligion", "TestWealth", "TestLiteracy",
                    "TestBusyness", 0);
    HumanGeneral hg (2, "TestBloodType", "TestGender", "TestRace", 0);

    Language l1 (1, "TestLanguage1", "TestFamily1", 0),
             l2 (2, "TestLanguage2", "TestFamily2", 0);

    HumanLanguage hl (2, {{l1, "Value1"}, {l2, "Value2"}}, 0);

    RepositoryContext &rcontext = context->getRepositoryContext();

    auto prepo = rcontext.getPlaceRepository();
    prepo->create(bplace);
    prepo->create(cplace);

    rcontext.getHumanRepository()->create(human);
    rcontext.getHumanAddressRepository()->create(ha);
    rcontext.getHumanLivingDatesRepository()->create(hld);
    rcontext.getHumanSocialRepository()->create(hs);
    rcontext.getHumanGeneralRepository()->create(hg);

    auto lrepo = rcontext.getLanguageRepository();
    lrepo->create(l1);
    lrepo->create(l2);

    rcontext.getHumanLanguageRepository()->create(hl);

    rcontext.getUserHumanRepository()->update(UserHuman(1, human));

    auto manager = context->getUserInfoManager();

    const UserMapper::Map ref_map
    {
        {"first_name", human.firstName},
        {"last_name", human.lastName},
        {"birth_place", human.birthPlace->name},
        {"address", ha.currentPlace->name},
        {"birth_date", std::to_string(hld.birthDate)},
        {"age", std::to_string(DateCommon::yearDiff(std::time(nullptr), hld.birthDate))},
        {"religion", hs.religion},
        {"wealth", hs.wealth},
        {"literacy", hs.literacy},
        {"busyness", hs.busyness},
        {"blood_type", hg.bloodType},
        {"gender", hg.gender},
        {"race", hg.race},
        {std::string("language_") + l1.name, "Value1"},
        {std::string("language_") + l2.name, "Value2"}
    };

    ASSERT_NO_THROW(ASSERT_EQ(manager->isHuman(hash_no_human), true));
    ASSERT_NO_THROW(ASSERT_EQ(manager->getHuman(hash_no_human), ref_map));
}

#endif

