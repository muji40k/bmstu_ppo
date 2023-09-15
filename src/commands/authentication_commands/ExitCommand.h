#ifndef _EXITCOMMAND_H_
#define _EXITCOMMAND_H_

#include <string>

#include "AuthenticationCommand.h"

class ExitCommand : public AuthenticationCommand
{
    public:
        ExitCommand(const std::string hash);
        virtual ~ExitCommand(void) override = default;
        virtual void execute(AppContext &context) override;

    private:
        const std::string hash;
};

DEF_EX(CommonExitCommandException, CommonAuthenticationCommandException,
       "Common ExitCommand exception");
DEF_EX(AllocationExitCommandException, CommonExitCommandException,
       "Unable to allocate LoginManager");

#endif

