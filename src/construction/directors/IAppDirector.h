#ifndef _IAPPDIRECTOR_H_
#define _IAPPDIRECTOR_H_

#include <memory>

#include "construction_exceptions.h"
#include "App.h"

class IAppDirector
{
    public:
        virtual ~IAppDirector(void) = default;
        virtual void construct(void) = 0;
        virtual std::shared_ptr<App> result(void) = 0;
};

DEF_EX(CommonAppDirectorException, ConstructionException,
       "Common AppDirector Exception");
DEF_EX(NullptrAppDirectorException, CommonAppDirectorException,
       "Nullptr occured");
DEF_EX(AllocationAppDirectorException, CommonAppDirectorException,
       "Allocation error");
DEF_EX(UnsupportedAppDirectorException, CommonAppDirectorException,
       "Type of the object is unsupported");
DEF_EX(WrongConfigurationAppDirectorException, CommonAppDirectorException,
       "Wrong configuration setup");
DEF_EX(NotReadyAppDirectorException, CommonAppDirectorException,
       "Object is not ready");

#endif

