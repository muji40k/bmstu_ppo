#include "MockRepositoryAbstractFactory.h"

#include "MockCountryRepository.h"
#include "MockHumanAddressRepository.h"
#include "MockHumanGeneralRepository.h"
#include "MockHumanLanguageRepository.h"
#include "MockHumanLivingDatesRepository.h"
#include "MockHumanRepository.h"
#include "MockHumanSocialRepository.h"
#include "MockLanguageRepository.h"
#include "MockMergeRequestRepository.h"
#include "MockPlaceCountryRepository.h"
#include "MockPlaceRepository.h"
#include "MockPlaceResourceRepository.h"
#include "MockResourceRepository.h"
#include "MockUserHumanRepository.h"
#include "MockUserRepository.h"
#include "MockUserRoleRepository.h"

#define ADD_REPO(type)                                                                                \
std::shared_ptr<I##type##Repository> MockRepositoryAbstractFactory::make##type##Repository(void)      \
try                                                                                                   \
{                                                                                                     \
    return std::static_pointer_cast<I##type##Repository>(std::make_shared<Mock##type##Repository>()); \
}                                                                                                     \
catch (std::bad_alloc &)                                                                              \
{                                                                                                     \
    throw CALL_EX(AllocationRepositoryAbstractFactoryException);                                      \
}

ADD_REPO(Country);
ADD_REPO(HumanAddress);
ADD_REPO(HumanGeneral);
ADD_REPO(HumanLanguage);
ADD_REPO(HumanLivingDates);
ADD_REPO(Human);
ADD_REPO(HumanSocial);
ADD_REPO(Language);
ADD_REPO(MergeRequest);
ADD_REPO(PlaceCountry);
ADD_REPO(Place);
ADD_REPO(PlaceResource);
ADD_REPO(Resource);
ADD_REPO(UserHuman);
ADD_REPO(User);
ADD_REPO(UserRole);

