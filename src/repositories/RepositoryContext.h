#ifndef _REPOSITORYCONTEXT_H_
#define _REPOSITORYCONTEXT_H_

#include <memory>

#include "repository_exceptions.h"

#include "RepositoryAbstractFactory.h"

class RepositoryContext
{
    public:
        RepositoryContext(std::shared_ptr<RepositoryAbstractFactory> factory);

#define ADD_REPO(type)                                                    \
    public:                                                               \
        std::shared_ptr<I##type##Repository> get##type##Repository(void); \
    private:                                                              \
        std::shared_ptr<I##type##Repository> _##type = nullptr

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

    private:
        std::shared_ptr<RepositoryAbstractFactory> factory;
};

DEF_EX(CommonRepositoryContextException, RepositoryException,
       "Common RespositoryContext Exception");
DEF_EX(FactoryNullptrRepositoryContextException, CommonRepositoryContextException,
       "Passed factory is represented with nullptr");
DEF_EX(AllocationRepositoryContextException, CommonRepositoryContextException,
       "Unable to allocate repository");

#endif

