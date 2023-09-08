#ifndef _IHUMANLANGUAGEREPOSITORY_H_
#define _IHUMANLANGUAGEREPOSITORY_H_

#include "IWriteRepository.h"
#include "ITimeChangeableRepository.h"
#include "HumanLanguage.h"

class IHumanLanguageRepository : public IWriteRepository<HumanLanguage>, public ITimeChangeableRepository<HumanLanguage>
{
    public:
        virtual ~IHumanLanguageRepository(void) override = default;
};

#endif

