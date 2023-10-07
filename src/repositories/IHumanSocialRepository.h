#ifndef _IHUMANSOCIALREPOSITORY_H_
#define _IHUMANSOCIALREPOSITORY_H_

#include "IWriteRepository.h"
#include "ITimeChangeableRepository.h"
#include "HumanSocial.h"

class IHumanSocialRepository : public IWriteRepository<HumanSocial>, public ITimeChangeableRepository<HumanSocial>
{
    public:
        virtual ~IHumanSocialRepository(void) override = default;
};

#endif

