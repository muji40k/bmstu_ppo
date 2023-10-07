#ifndef _IUSERROLEREPOSITORY_H_
#define _IUSERROLEREPOSITORY_H_

#include "IWriteRepository.h"
#include "IReadRepository.h"
#include "UserRole.h"

class IUserRoleRepository : public IWriteRepository<UserRole>, public IReadRepository<UserRole>
{
    public:
        virtual ~IUserRoleRepository(void) override = default;
};

#endif

