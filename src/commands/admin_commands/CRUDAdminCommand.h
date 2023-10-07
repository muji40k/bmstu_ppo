#ifndef _CRUDADMINCOMMAND_H_
#define _CRUDADMINCOMMAND_H_

#include <string>

#include "AdminCommand.h"
#include "AdminInfoManager.h"

class CRUDAdminCommand : public AdminCommand
{
    public:
        CRUDAdminCommand(const std::string hash, AdminInfoStrategy &strategy);
        virtual ~CRUDAdminCommand(void) override = default;
        virtual void execute(AppContext &context) override;

    private:
        const std::string hash;
        AdminInfoStrategy &strategy;
};

DEF_EX(CommonCRUDAdminCommandException, CommonAdminCommandException,
       "Common CRUDAdminCommand exception");
DEF_EX(AllocationCRUDAdminCommandException, CommonCRUDAdminCommandException,
       "Unable to allocate CRUDAdminManager");
DEF_EX(NotAuthenticatedCRUDAdminCommandException, CommonCRUDAdminCommandException,
       "Hash doesn't specify any user");
DEF_EX(NotAuthorizedCRUDAdminCommandException, CommonCRUDAdminCommandException,
       "User isn't an admin");
DEF_EX(StrategyCRUDAdminCommandException, CommonCRUDAdminCommandException, "");
DEF_EX(RepositoryCRUDAdminCommandException, CommonCRUDAdminCommandException, "");

#endif

