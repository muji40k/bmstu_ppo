#ifndef _ICOMMANDRESULT_H_
#define _ICOMMANDRESULT_H_

#include "AppContext.h"

template <typename Type>
class ICommandResult
{
    public:
        virtual ~ICommandResult(void) = default;
        virtual const Type &result(void) = 0;
};

#endif

