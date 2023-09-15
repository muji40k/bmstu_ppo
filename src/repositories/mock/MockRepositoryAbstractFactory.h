#ifndef _MOCKREPOSITORYABSTRACTFACTORY_H_
#define _MOCKREPOSITORYABSTRACTFACTORY_H_

#include "RepositoryAbstractFactory.h"

class MockRepositoryAbstractFactory : public RepositoryAbstractFactory
{
    public:
        virtual ~MockRepositoryAbstractFactory(void) = default;

#define ADD_REPO(type) \
        virtual std::shared_ptr<I##type##Repository> make##type##Repository(void) override

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

#endif

