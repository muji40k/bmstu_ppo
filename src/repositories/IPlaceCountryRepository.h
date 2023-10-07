#ifndef _IPLACECOUNTRYREPOSITORY_H_
#define _IPLACECOUNTRYREPOSITORY_H_

#include "IWriteRepository.h"
#include "ITimeChangeableRepository.h"
#include "PlaceCountry.h"

class IPlaceCountryRepository : public IWriteRepository<PlaceCountry>, public ITimeChangeableRepository<PlaceCountry>
{
    public:
        virtual ~IPlaceCountryRepository(void) override = default;
};

#endif

