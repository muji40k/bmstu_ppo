#include <gtest/gtest.h>

#include "TestAdminInfoManager.h"
#include "TestAdminRequestManager.h"
#include "TestAuthorizationManager.h"
#include "TestLoginManager.h"
#include "TestQueryManager.h"
#include "TestUserInfoManager.h"
#include "TestUserRequestManager.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

