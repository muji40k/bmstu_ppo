#ifndef _IUSERHUMANREPOSITORY_H_
#define _IUSERHUMANREPOSITORY_H_

#include "IWriteRepository.h"
#include "IReadRepository.h"
#include "UserHuman.h"

class IUserHumanRepository : public IWriteRepository<UserHuman>, public IReadRepository<UserHuman>
{
    public:
        virtual ~IUserHumanRepository(void) override = default;
};

#endif

