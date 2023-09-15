#ifndef _MOCKHUMANLANGUAGEREPOSITORY_H_
#define _MOCKHUMANLANGUAGEREPOSITORY_H_

#include "IHumanLanguageRepository.h"
#include "MockGenericTimeChangeableRepository.h"

class MockHumanLanguageRepository : public IHumanLanguageRepository
{
    public:
        virtual ~MockHumanLanguageRepository(void) override = default;
        virtual void create(const HumanLanguage &item) override;
        virtual void update(const HumanLanguage &item) override;
        virtual void erase(const HumanLanguage &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<HumanLanguage>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<HumanLanguage>> getAll(void) override;

    private:
        MockGenericTimeChangeableRepository<HumanLanguage> impl;
};

#endif

