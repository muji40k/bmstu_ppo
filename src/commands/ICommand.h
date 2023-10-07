#ifndef _ICOMMAND_H_
#define _ICOMMAND_H_

#include "facade_exception.h"

#include "AppContext.h"

class ICommand
{
    public:
        virtual ~ICommand(void) = default;
        virtual void execute(AppContext &context) = 0;
};

DEF_EX(CommonCommandException, FacadeException, "Common Command exception");

#endif

