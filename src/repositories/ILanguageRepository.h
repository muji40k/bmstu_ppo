#ifndef _ILANGUAGEREPOSITORY_H_
#define _ILANGUAGEREPOSITORY_H_

#include "IWriteRepository.h"
#include "ITimeChangeableRepository.h"
#include "Language.h"

class ILanguageRepository : public IWriteRepository<Language>, public ITimeChangeableRepository<Language>
{
    public:
        virtual ~ILanguageRepository(void) override = default;
};

#endif

