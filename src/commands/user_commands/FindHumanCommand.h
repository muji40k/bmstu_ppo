#ifndef _FINDHUMANCOMMAND_H_
#define _FINDHUMANCOMMAND_H_

#include <string>
#include <list>

#include "UserCommand.h"
#include "ICommandResult.h"
#include "UserMapper.h"

class FindHumanCommand : public UserCommand,
                         public ICommandResult<std::list<UserMapper::Map>>
{
    public:
        FindHumanCommand(const std::string hash, const UserMapper::Map map);
        virtual ~FindHumanCommand(void) override = default;
        virtual void execute(AppContext &context) override;
        virtual const std::list<UserMapper::Map> &result(void) override;

    private:
        const std::string hash;
        const UserMapper::Map in_map;
        std::list<UserMapper::Map> out;
};

DEF_EX(CommonFindHumanCommandException, CommonUserCommandException,
       "Common FindHumanCommand exception");
DEF_EX(AllocationFindHumanCommandException, CommonFindHumanCommandException,
       "Unable to allocate FindHumanManager");
DEF_EX(NotAuthenticatedFindHumanCommandException, CommonFindHumanCommandException,
       "User not authenticated");
DEF_EX(NotAuthorizedFindHumanCommandException, CommonFindHumanCommandException,
       "User not authorized");
DEF_EX(WrongDataFindHumanCommandException, CommonFindHumanCommandException, "");
DEF_EX(RepositoryFindHumanCommandException, CommonFindHumanCommandException, "");

#endif

