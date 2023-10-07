#ifndef _MOCKCOUNTRYREPOSITORY_H_
#define _MOCKCOUNTRYREPOSITORY_H_

#include "ICountryRepository.h"
#include "MockGenericTimeChangeableRepository.h"

class MockCountryRepository : public ICountryRepository
{
    public:
        virtual ~MockCountryRepository(void) override = default;
        virtual void create(const Country &item) override;
        virtual void update(const Country &item) override;
        virtual void erase(const Country &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<Country>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<Country>> getAll(void) override;

    private:
        MockGenericTimeChangeableRepository<Country> impl;
};

#endif

