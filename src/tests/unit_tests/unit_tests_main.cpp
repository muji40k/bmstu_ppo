#include "unit_tests_main.h"

#include <gtest/gtest.h>

#include "TestAdminInfoManager.h"
#include "TestAdminRequestManager.h"
#include "TestAuthorizationManager.h"
#include "TestLoginManager.h"
#include "TestQueryManager.h"
#include "TestUserInfoManager.h"
#include "TestUserRequestManager.h"

void unit_tests_main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
}

