#ifndef _ISADMINCOMMAND_H_
#define _ISADMINCOMMAND_H_

#include <string>

#include "AuthorizationCommand.h"
#include "ICommandResult.h"

class IsAdminCommand : public AuthorizationCommand, public ICommandResult<bool>
{
    public:
        IsAdminCommand(const std::string hash);
        virtual ~IsAdminCommand(void) override = default;
        virtual void execute(AppContext &context) override;
        virtual const bool &result(void) override;

    private:
        const std::string hash;
        bool res = false;
};

DEF_EX(CommonIsAdminCommandException, CommonAuthorizationCommandException,
       "Common IsAuthenticatedCommand exception");
DEF_EX(AllocationIsAdminCommandException, CommonIsAdminCommandException,
       "Unable to allocate manager");
DEF_EX(NotAuthenticatedIsAdminCommandException, CommonIsAdminCommandException,
       "Unable to allocate manager");
DEF_EX(RepositoryIsAdminCommandException, CommonIsAdminCommandException, "");

#endif

