#ifndef _LOGINCOMMAND_H_
#define _LOGINCOMMAND_H_

#include <string>

#include "AuthenticationCommand.h"
#include "ICommandResult.h"

class LoginCommand : public AuthenticationCommand, public ICommandResult<std::string>
{
    public:
        LoginCommand(const std::string email, const std::string password);
        virtual ~LoginCommand(void) override = default;
        virtual void execute(AppContext &context) override;
        virtual const std::string &result(void) override;

    private:
        const std::string email;
        const std::string password;
        std::string hash;
        bool ready = false;
};

DEF_EX(CommonLoginCommandException, CommonAuthenticationCommandException,
       "Common LoginCommand exception");
DEF_EX(AllocationLoginCommandException, CommonLoginCommandException,
       "Unable to allocate LoginManager");
DEF_EX(NotPerformedLoginCommandException, CommonLoginCommandException,
       "Login wasn't performed");
DEF_EX(WrongLoginCommandException, CommonLoginCommandException,
       "Incorrect login");
DEF_EX(AlreadyLoggedinCommandException, CommonLoginCommandException,
       "User already authenticated");
DEF_EX(RepositoryLoginCommandException, CommonLoginCommandException, "");

#endif

