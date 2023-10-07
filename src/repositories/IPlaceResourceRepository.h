#ifndef _IPLACERESOURCEREPOSITORY_H_
#define _IPLACERESOURCEREPOSITORY_H_

#include "IWriteRepository.h"
#include "ITimeChangeableRepository.h"
#include "PlaceResource.h"

class IPlaceResourceRepository : public IWriteRepository<PlaceResource>, public ITimeChangeableRepository<PlaceResource>
{
    public:
        virtual ~IPlaceResourceRepository(void) override = default;
};

#endif

