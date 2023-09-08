#ifndef _FACADE_H_
#define _FACADE_H_

#include <memory>

#include "facade_exception.h"

#include "AppContext.h"

#include "ICommand.h"

class Facade
{
    public:
        Facade(std::shared_ptr<AppContext> context);
        virtual ~Facade(void) = default;

        virtual void run(ICommand &command);

    private:
        std::shared_ptr<AppContext> context;
};

DEF_EX(CommonFacadeException, FacadeException, "Common Facade exception");
DEF_EX(NullptrFacadeException, CommonFacadeException,
       "AppContext represented with nullptr");

#endif

