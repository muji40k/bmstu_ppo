#ifndef _IHUMANREPOSITORY_H_
#define _IHUMANREPOSITORY_H_

#include "IWriteRepository.h"
#include "ITimeChangeableRepository.h"
#include "Human.h"

class IHumanRepository : public IWriteRepository<Human>, public ITimeChangeableRepository<Human>
{
    public:
        virtual ~IHumanRepository(void) override = default;
};

#endif

