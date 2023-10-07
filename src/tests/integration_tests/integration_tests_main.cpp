#include "integration_tests_main.h"

#include <gtest/gtest.h>

#include "TestPSQLCountryRepository.h"
#include "TestPSQLHumanAddressRepository.h"
#include "TestPSQLHumanGeneralRepository.h"
#include "TestPSQLHumanLanguageRepository.h"
#include "TestPSQLHumanLivingDatesRepository.h"
#include "TestPSQLHumanRepository.h"
#include "TestPSQLHumanSocialRepository.h"
#include "TestPSQLLanguageRepository.h"
#include "TestPSQLMergeRequestRepository.h"
#include "TestPSQLPlaceCountryRepository.h"
#include "TestPSQLPlaceRepository.h"
#include "TestPSQLPlaceResourceRepository.h"
#include "TestPSQLResourceRepository.h"
#include "TestPSQLUserHumanRepository.h"
#include "TestPSQLUserRepository.h"
#include "TestPSQLUserRoleRepository.h"

void integration_tests_main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
}

