#ifndef _REPOSITORYABSTRACTFACTORY_H_
#define _REPOSITORYABSTRACTFACTORY_H_

#include <memory>

#include "repository_exceptions.h"

#include "ICountryRepository.h"
#include "IHumanAddressRepository.h"
#include "IHumanGeneralRepository.h"
#include "IHumanLanguageRepository.h"
#include "IHumanLivingDatesRepository.h"
#include "IHumanRepository.h"
#include "IHumanSocialRepository.h"
#include "ILanguageRepository.h"
#include "IMergeRequestRepository.h"
#include "IPlaceCountryRepository.h"
#include "IPlaceRepository.h"
#include "IPlaceResourceRepository.h"
#include "IResourceRepository.h"
#include "IUserHumanRepository.h"
#include "IUserRepository.h"
#include "IUserRoleRepository.h"

class RepositoryAbstractFactory
{
    public:
        virtual ~RepositoryAbstractFactory(void) = default;

#define ADD_REPO(type) \
        virtual std::shared_ptr<I##type##Repository> make##type##Repository(void) = 0

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

#undef ADD_REPO
};

DEF_EX(CommonRepositoryAbstractFactoryException, RepositoryException,
       "Common RepositoryAbstractFactory exception");
DEF_EX(AllocationRepositoryAbstractFactoryException,
       CommonRepositoryAbstractFactoryException,
       "RepositoryAbstractFactory allocation error occured");

#endif

