#ifndef _IUSERREPOSITORY_H_
#define _IUSERREPOSITORY_H_

#include "IWriteRepository.h"
#include "IReadRepository.h"
#include "User.h"

class IUserRepository : public IWriteRepository<User>, public IReadRepository<User>
{
    public:
        virtual ~IUserRepository(void) override = default;
};

#endif

