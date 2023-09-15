#ifndef _GETREQUESTSCOMMAND_H_
#define _GETREQUESTSCOMMAND_H_

#include <memory>
#include <string>

#include "AdminCommand.h"
#include "ICommandResult.h"
#include "AdminRequestManager.h"

class GetRequestsCommand : public AdminCommand,
                           public ICommandResult<std::shared_ptr<RequestSet>>
{
    public:
        GetRequestsCommand(const std::string hash);
        virtual ~GetRequestsCommand(void) override = default;
        virtual void execute(AppContext &context) override;
        virtual const std::shared_ptr<RequestSet> &result(void) override;

    private:
        const std::string hash;
        std::shared_ptr<RequestSet> set = nullptr;
};

DEF_EX(CommonGetRequestsCommandException, CommonAdminCommandException,
       "Common GetRequestsCommand exception");
DEF_EX(AllocationGetRequestsCommandException, CommonGetRequestsCommandException,
       "Unable to allocate GetRequestsManager");
DEF_EX(NotAuthenticatedGetRequestsCommandException, CommonGetRequestsCommandException,
       "Hash doesn't specify any user");
DEF_EX(NotAuthorizedGetRequestsCommandException, CommonGetRequestsCommandException,
       "User isn't an admin");
DEF_EX(NotPrerformedGetRequestsCommandException, CommonGetRequestsCommandException,
       "Command wasn't executed");
DEF_EX(RepositoryGetRequestsCommandException, CommonGetRequestsCommandException, "");

#endif

