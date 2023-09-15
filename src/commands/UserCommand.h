#ifndef _USERCOMMAND_H_
#define _USERCOMMAND_H_

#include "ICommand.h"

class UserCommand : public ICommand
{};

DEF_EX(CommonUserCommandException, CommonCommandException,
       "Common UserCommand exception");

#endif

