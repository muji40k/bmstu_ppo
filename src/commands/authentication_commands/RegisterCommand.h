#ifndef _REGISTERCOMMAND_H_
#define _REGISTERCOMMAND_H_

#include <string>

#include "AuthenticationCommand.h"
#include "User.h"

class RegisterCommand : public AuthenticationCommand
{
    public:
        RegisterCommand(const std::string name, const std::string email,
                        const std::string password);
        virtual ~RegisterCommand(void) override = default;
        virtual void execute(AppContext &context) override;

    private:
        const User user;
};

DEF_EX(CommonRegisterCommandException, CommonAuthenticationCommandException,
       "Common RegisterCommand exception");
DEF_EX(AllocationRegisterCommandException, CommonRegisterCommandException,
       "Unable to allocate LoginManager");
DEF_EX(AlreadyRegisteredCommandException, CommonRegisterCommandException,
       "User already authenticated");
DEF_EX(RepositoryRegisterCommandException, CommonRegisterCommandException, "");

#endif

