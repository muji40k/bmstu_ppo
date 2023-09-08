#ifndef _IHUMANGENERALREPOSITORY_H_
#define _IHUMANGENERALREPOSITORY_H_

#include "IWriteRepository.h"
#include "ITimeChangeableRepository.h"
#include "HumanGeneral.h"

class IHumanGeneralRepository : public IWriteRepository<HumanGeneral>, public ITimeChangeableRepository<HumanGeneral>
{
    public:
        virtual ~IHumanGeneralRepository(void) override = default;
};

#endif

