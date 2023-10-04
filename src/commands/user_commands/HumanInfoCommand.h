#ifndef _HUMANINFOCOMMAND_H_
#define _HUMANINFOCOMMAND_H_

#include <string>
#include <utility>

#include "UserCommand.h"
#include "ICommandResult.h"
#include "UserMapper.h"

class HumanInfoCommand : public UserCommand,
                         public ICommandResult<std::pair<bool, UserMapper::Map>>
{
    public:
        HumanInfoCommand(const std::string hash);
        virtual ~HumanInfoCommand(void) override = default;
        virtual void execute(AppContext &context) override;
        virtual const std::pair<bool, UserMapper::Map> &result(void) override;

    private:
        const std::string hash;
        std::pair<bool, UserMapper::Map> out;
};

DEF_EX(CommonHumanInfoCommandException, CommonUserCommandException,
       "Common HumanInfoCommand exception");
DEF_EX(AllocationHumanInfoCommandException, CommonHumanInfoCommandException,
       "Unable to allocate HumanInfoManager");
DEF_EX(NotAuthenticatedHumanInfoCommandException, CommonHumanInfoCommandException,
       "User not authenticated");
DEF_EX(NotAuthorizedHumanInfoCommandException, CommonHumanInfoCommandException,
       "User not authorized");
DEF_EX(RepositoryHumanInfoCommandException, CommonHumanInfoCommandException, "");

#endif

