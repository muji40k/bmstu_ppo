#ifndef _IAPPCONTEXTDIRECTOR_H_
#define _IAPPCONTEXTDIRECTOR_H_

#include <memory>

#include "construction_exceptions.h"
#include "AppContext.h"

class IAppContextDirector
{
    public:
        virtual ~IAppContextDirector(void) = default;
        virtual void construct(void) = 0;
        virtual std::shared_ptr<AppContext> result(void) = 0;
};

DEF_EX(CommonAppContextDirectorException, ConstructionException,
       "Common AppContextDirector Exception");
DEF_EX(NullptrAppContextDirectorException, CommonAppContextDirectorException,
       "Nullptr occured");
DEF_EX(AllocationAppContextDirectorException, CommonAppContextDirectorException,
       "Allocation error");
DEF_EX(UnsupportedAppContextDirectorException, CommonAppContextDirectorException,
       "Type of the object is unsupported");
DEF_EX(WrongConfigurationAppContextDirectorException, CommonAppContextDirectorException,
       "Wrong configuration setup");
DEF_EX(NotReadyAppContextDirectorException, CommonAppContextDirectorException,
       "Object is not ready");

#endif

