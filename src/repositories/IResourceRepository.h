#ifndef _IRESOURCEREPOSITORY_H_
#define _IRESOURCEREPOSITORY_H_

#include "IWriteRepository.h"
#include "ITimeChangeableRepository.h"
#include "Resource.h"

class IResourceRepository : public IWriteRepository<Resource>, public ITimeChangeableRepository<Resource>
{
    public:
        virtual ~IResourceRepository(void) override = default;
};

#endif

