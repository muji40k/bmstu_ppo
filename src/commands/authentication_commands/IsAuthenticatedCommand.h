#ifndef _ISAUTHENTICATEDCOMMAND_H_
#define _ISAUTHENTICATEDCOMMAND_H_

#include <string>

#include "AuthenticationCommand.h"
#include "ICommandResult.h"

class IsAuthenticatedCommand : public AuthenticationCommand, public ICommandResult<bool>
{
    public:
        IsAuthenticatedCommand(const std::string hash);
        virtual ~IsAuthenticatedCommand(void) override = default;
        virtual void execute(AppContext &context) override;
        virtual const bool &result(void) override;

    private:
        const std::string hash;
        bool res = false;
};

DEF_EX(CommonIsAuthenticatedCommandException, CommonAuthenticationCommandException,
       "Common IsAuthenticatedCommand exception");
DEF_EX(AllocationIsAuthenticatedCommandException, CommonIsAuthenticatedCommandException,
       "Unable to allocate LoginManager");

#endif

