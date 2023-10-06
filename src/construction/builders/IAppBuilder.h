#ifndef _IAPPBUILDER_H_
#define _IAPPBUILDER_H_

#include <memory>

#include "construction_exceptions.h"

#include "App.h"
#include "AppContext.h"

class IAppBuilder
{
    public:
        virtual ~IAppBuilder(void) = default;
        virtual void setAppContext(std::shared_ptr<AppContext> context) = 0;
        virtual void build(void) = 0;
        virtual std::shared_ptr<App> result(void) = 0;
};

DEF_EX(CommonAppBuilderException, ConstructionException,
       "Common AppBuilder Exception");
DEF_EX(NullptrAppBuilderException, CommonAppBuilderException,
       "Nullptr occured");
DEF_EX(WrongDataAppBuilderException, CommonAppBuilderException,
       "Wrong data occured");
DEF_EX(AllocationAppBuilderException, CommonAppBuilderException,
       "Allocation error");
DEF_EX(NotReadyAppBuilderException, CommonAppBuilderException,
       "Object is not ready");

#endif

