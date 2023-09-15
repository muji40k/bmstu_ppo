#ifndef _QUERYCOMMAND_H_
#define _QUERYCOMMAND_H_

#include "ICommand.h"

class QueryCommand : public ICommand
{};

DEF_EX(CommonQueryCommandException, CommonCommandException,
       "Common QueryCommand exception");

#endif

