#ifndef _ADMINCOMMAND_H_
#define _ADMINCOMMAND_H_

#include "ICommand.h"

class AdminCommand : public ICommand
{};

DEF_EX(CommonAdminCommandException, CommonCommandException,
       "Common AdminCommand exception");

#endif

