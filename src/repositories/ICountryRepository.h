#ifndef _ICOUNTRYREPOSITORY_H_
#define _ICOUNTRYREPOSITORY_H_

#include "IWriteRepository.h"
#include "ITimeChangeableRepository.h"
#include "Country.h"

class ICountryRepository : public IWriteRepository<Country>, public ITimeChangeableRepository<Country>
{
    public:
        virtual ~ICountryRepository(void) override = default;
};

#endif

