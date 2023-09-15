#ifndef _SETUSERINFOCOMMAND_H_
#define _SETUSERINFOCOMMAND_H_

#include <string>

#include "UserCommand.h"
#include "UserMapper.h"

class SetUserInfoCommand : public UserCommand
{
    public:
        SetUserInfoCommand(const std::string hash, const UserMapper::Map map);
        virtual ~SetUserInfoCommand(void) override = default;
        virtual void execute(AppContext &context) override;

    private:
        const std::string hash;
        const UserMapper::Map map;
};

DEF_EX(CommonSetUserInfoCommandException, CommonUserCommandException,
       "Common SetUserInfoCommand exception");
DEF_EX(AllocationSetUserInfoCommandException, CommonSetUserInfoCommandException,
       "Unable to allocate SetUserInfoManager");
DEF_EX(NotAuthenticatedSetUserInfoCommandException, CommonSetUserInfoCommandException,
       "User not authenticated");
DEF_EX(UnexpectedKeySetUserInfoCommandException, CommonSetUserInfoCommandException,
       "Map contains unexpected keys");
DEF_EX(RepositorySetUserInfoCommandException, CommonSetUserInfoCommandException, "");

#endif

