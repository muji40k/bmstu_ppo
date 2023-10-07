#ifndef _IHUMANADDRESSREPOSITORY_H_
#define _IHUMANADDRESSREPOSITORY_H_

#include "IWriteRepository.h"
#include "ITimeChangeableRepository.h"
#include "HumanAddress.h"

class IHumanAddressRepository : public IWriteRepository<HumanAddress>, public ITimeChangeableRepository<HumanAddress>
{
    public:
        virtual ~IHumanAddressRepository(void) override = default;
};

#endif

