#ifndef _AUTHENTICATIONCOMMAND_H_
#define _AUTHENTICATIONCOMMAND_H_

#include "ICommand.h"

class AuthenticationCommand : public ICommand
{};

DEF_EX(CommonAuthenticationCommandException, CommonCommandException,
       "Common AuthenticationCommand exception");

#endif

