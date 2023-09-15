#ifndef _SETHUMANCOMMAND_H_
#define _SETHUMANCOMMAND_H_

#include <string>
#include <list>

#include "UserCommand.h"
#include "UserMapper.h"

class SetHumanCommand : public UserCommand
{
    public:
        SetHumanCommand(const std::string hash, const UserMapper::Map map);
        virtual ~SetHumanCommand(void) override = default;
        virtual void execute(AppContext &context) override;

    private:
        const std::string hash;
        const UserMapper::Map in_map;
};

DEF_EX(CommonSetHumanCommandException, CommonUserCommandException,
       "Common SetHumanCommand exception");
DEF_EX(AllocationSetHumanCommandException, CommonSetHumanCommandException,
       "Unable to allocate SetHumanManager");
DEF_EX(NotAuthenticatedSetHumanCommandException, CommonSetHumanCommandException,
       "User not authenticated");
DEF_EX(NotFoundSetHumanCommandException, CommonSetHumanCommandException,
       "Requested human not found");
DEF_EX(WrongDataSetHumanCommandException, CommonSetHumanCommandException, "");
DEF_EX(RepositorySetHumanCommandException, CommonSetHumanCommandException, "");

#endif

