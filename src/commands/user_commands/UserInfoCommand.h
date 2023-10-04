#ifndef _USERINFOCOMMAND_H_
#define _USERINFOCOMMAND_H_

#include <string>

#include "UserCommand.h"
#include "ICommandResult.h"
#include "UserMapper.h"

class UserInfoCommand : public UserCommand, public ICommandResult<UserMapper::Map>
{
    public:
        UserInfoCommand(const std::string hash);
        virtual ~UserInfoCommand(void) override = default;
        virtual void execute(AppContext &context) override;
        virtual const UserMapper::Map &result(void) override;

    private:
        const std::string hash;
        UserMapper::Map map;
};

DEF_EX(CommonUserInfoCommandException, CommonUserCommandException,
       "Common UserInfoCommand exception");
DEF_EX(AllocationUserInfoCommandException, CommonUserInfoCommandException,
       "Unable to allocate UserInfoManager");
DEF_EX(NotAuthenticatedUserInfoCommandException, CommonUserInfoCommandException,
       "User not authenticated");
DEF_EX(NotAuthorizedUserInfoCommandException, CommonUserInfoCommandException,
       "User not authorized");
DEF_EX(RepositoryUserInfoCommandException, CommonUserInfoCommandException, "");

#endif

