#ifndef _IREPOSITORYCONTEXTDIRECTOR_H_
#define _IREPOSITORYCONTEXTDIRECTOR_H_

#include <memory>

#include "construction_exceptions.h"

#include "RepositoryContext.h"
#include "RegistrationHook.h"
#include "AuthorizationHook.h"

class IRepositoryContextDirector
{
    public:
        virtual ~IRepositoryContextDirector(void) = default;
        virtual void construct(void) = 0;
        virtual std::shared_ptr<RepositoryContext> result(void) = 0;
        virtual const std::list<std::shared_ptr<RegistrationHook::Item>> &registrationHooks(void) = 0;
        virtual const std::list<std::shared_ptr<AuthorizationHook::Item>> &authorizationHooks(void) = 0;
};

DEF_EX(CommonRepositoryContextDirectorException, ConstructionException,
       "Common RepositoryContextDirector Exception");
DEF_EX(NullptrRepositoryContextDirectorException, CommonRepositoryContextDirectorException,
       "Nullptr occured");
DEF_EX(AllocationRepositoryContextDirectorException, CommonRepositoryContextDirectorException,
       "Allocation error");
DEF_EX(UnsupportedRepositoryContextDirectorException, CommonRepositoryContextDirectorException,
       "Type of the object is unsupported");
DEF_EX(WrongConfigurationRepositoryContextDirectorException, CommonRepositoryContextDirectorException,
       "Wrong configuration setup");
DEF_EX(NotReadyRepositoryContextDirectorException, CommonRepositoryContextDirectorException,
       "Object is not ready");

#endif

