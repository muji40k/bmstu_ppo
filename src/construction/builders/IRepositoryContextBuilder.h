#ifndef _IREPOSITORYCONTEXTBUILDER_H_
#define _IREPOSITORYCONTEXTBUILDER_H_

#include <memory>

#include "construction_exceptions.h"

#include "AppContext.h"
#include "RepositoryContext.h"

#include "RegistrationHook.h"
#include "AuthorizationHook.h"

class IRepositoryContextBuilder
{
    public:
        virtual ~IRepositoryContextBuilder(void) = default;
        virtual void build(void) = 0;
        virtual std::shared_ptr<RepositoryContext> result(void) = 0;
        virtual const std::list<std::shared_ptr<RegistrationHook::Item>> &registrationHooks(void) = 0;
        virtual const std::list<std::shared_ptr<AuthorizationHook::Item>> &authorizationHooks(void) = 0;
};

DEF_EX(CommonRepositoryContextBuilderException, ConstructionException,
       "Common RepositoryContextBuilder Exception");
DEF_EX(NullptrRepositoyContextBuilderException, CommonRepositoryContextBuilderException,
       "Nullptr occured");
DEF_EX(WrongDataRepositoryContextBuilderException, CommonRepositoryContextBuilderException,
       "Wrong data occured");
DEF_EX(AllocationRepositoryContextBuilderException, CommonRepositoryContextBuilderException,
       "Allocation error");
DEF_EX(NotReadyRepositoryContextBuilderException, CommonRepositoryContextBuilderException,
       "Object is not ready");

#endif

