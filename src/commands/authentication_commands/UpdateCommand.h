#ifndef _UPDATECOMMAND_H_
#define _UPDATECOMMAND_H_

#include <string>

#include "AuthenticationCommand.h"
#include "ICommandResult.h"

class UpdateCommand : public AuthenticationCommand, public ICommandResult<std::string>
{
    public:
        UpdateCommand(const std::string hash);
        virtual ~UpdateCommand(void) override = default;
        virtual void execute(AppContext &context) override;
        virtual const std::string &result(void) override;

    private:
        const std::string inhash;
        std::string hash;
        bool ready = false;
};

DEF_EX(CommonUpdateCommandException, CommonAuthenticationCommandException,
       "Common UpdateCommand exception");
DEF_EX(AllocationUpdateCommandException, CommonUpdateCommandException,
       "Unable to allocate LoginManager");
DEF_EX(NotPerformedUpdateCommandException, CommonUpdateCommandException,
       "Update wasn't performed");
DEF_EX(NotAuthenticatedUpdateCommandException, CommonUpdateCommandException,
       "User isn't authenticated");
DEF_EX(NoUserUpdateCommandException, CommonUpdateCommandException,
       "User doesn't exist");
DEF_EX(AlreadyLoggedinUpdateCommandException, CommonUpdateCommandException,
       "User already authenticated");
DEF_EX(RepositoryUpdateCommandException, CommonUpdateCommandException, "");

#endif

