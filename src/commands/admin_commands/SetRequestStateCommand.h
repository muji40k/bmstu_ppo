#ifndef _SETREQUESTSTATECOMMAND_H_
#define _SETREQUESTSTATECOMMAND_H_

#include <string>

#include "AdminCommand.h"
#include "MergeRequest.h"

class SetRequestStateCommand : public AdminCommand
{
    public:
        SetRequestStateCommand(const std::string hash, const MergeRequest mr);
        virtual ~SetRequestStateCommand(void) override = default;
        virtual void execute(AppContext &context) override;

    private:
        const std::string hash;
        const MergeRequest mr;
};

DEF_EX(CommonSetRequestStateCommandException, CommonAdminCommandException,
       "Common SetRequestStateCommand exception");
DEF_EX(AllocationSetRequestStateCommandException, CommonSetRequestStateCommandException,
       "Unable to allocate SetRequestStateManager");
DEF_EX(NotAuthenticatedSetRequestStateCommandException, CommonSetRequestStateCommandException,
       "Hash doesn't specify any user");
DEF_EX(NotAuthorizedSetRequestStateCommandException, CommonSetRequestStateCommandException,
       "User isn't an admin");
DEF_EX(NoHandlerSetRequestStateCommandException, CommonSetRequestStateCommandException,
       "State isn't supported");
DEF_EX(RepositorySetRequestStateCommandException, CommonSetRequestStateCommandException, "");

#endif

