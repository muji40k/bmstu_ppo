#ifndef _IAPPCONTEXTBUILDER_H_
#define _IAPPCONTEXTBUILDER_H_

#include <memory>

#include "construction_exceptions.h"

#include "AppContext.h"
#include "RepositoryContext.h"

#include "RegistrationHook.h"
#include "AuthorizationHook.h"

class IAppContextBuilder
{
    public:
        virtual ~IAppContextBuilder(void) = default;
        virtual void setRepositoryContext(std::shared_ptr<RepositoryContext> context) = 0;
        virtual void setRegistrationHooks(const std::list<std::shared_ptr<RegistrationHook::Item>> &hooks) = 0;
        virtual void setAuthorizationHooks(const std::list<std::shared_ptr<AuthorizationHook::Item>> &hooks) = 0;
        virtual void build(void) = 0;
        virtual std::shared_ptr<AppContext> result(void) = 0;
};

DEF_EX(CommonAppContextBuilderException, ConstructionException,
       "Common AppContextBuilder Exception");
DEF_EX(NullptrAppContextBuilderException, CommonAppContextBuilderException,
       "Nullptr occured");
DEF_EX(WrongDataAppContextBuilderException, CommonAppContextBuilderException,
       "Wrong data occured");
DEF_EX(AllocationAppContextBuilderException, CommonAppContextBuilderException,
       "Allocation error");
DEF_EX(NotReadyAppContextBuilderException, CommonAppContextBuilderException,
       "Object is not ready");

#endif

