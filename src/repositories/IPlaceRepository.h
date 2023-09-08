#ifndef _IPLACEREPOSITORY_H_
#define _IPLACEREPOSITORY_H_

#include "IWriteRepository.h"
#include "ITimeChangeableRepository.h"
#include "Place.h"

class IPlaceRepository : public IWriteRepository<Place>, public ITimeChangeableRepository<Place>
{
    public:
        virtual ~IPlaceRepository(void) override = default;
};

#endif

