#ifndef _IHUMANLIVINGDATESREPOSITORY_H_
#define _IHUMANLIVINGDATESREPOSITORY_H_

#include "IWriteRepository.h"
#include "ITimeChangeableRepository.h"
#include "HumanLivingDates.h"

class IHumanLivingDatesRepository : public IWriteRepository<HumanLivingDates>, public ITimeChangeableRepository<HumanLivingDates>
{
    public:
        virtual ~IHumanLivingDatesRepository(void) override = default;
};

#endif

