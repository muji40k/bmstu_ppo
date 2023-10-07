#ifndef _AUTHORIZATIONCOMMAND_H_
#define _AUTHORIZATIONCOMMAND_H_

#include "ICommand.h"

class AuthorizationCommand : public ICommand
{};

DEF_EX(CommonAuthorizationCommandException, CommonCommandException,
       "Common AuthenticationCommand exception");

#endif

