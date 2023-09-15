#ifndef _MOCKLANGUAGEREPOSITORY_H_
#define _MOCKLANGUAGEREPOSITORY_H_

#include "ILanguageRepository.h"
#include "MockGenericTimeChangeableRepository.h"

class MockLanguageRepository : public ILanguageRepository
{
    public:
        virtual ~MockLanguageRepository(void) override = default;
        virtual void create(const Language &item) override;
        virtual void update(const Language &item) override;
        virtual void erase(const Language &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<Language>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<Language>> getAll(void) override;

    private:
        MockGenericTimeChangeableRepository<Language> impl;
};

#endif

