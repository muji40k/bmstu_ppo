#ifndef _MOCKRESOURCEREPOSITORY_H_
#define _MOCKRESOURCEREPOSITORY_H_

#include "IResourceRepository.h"
#include "MockGenericTimeChangeableRepository.h"

class MockResourceRepository : public IResourceRepository
{
    public:
        virtual ~MockResourceRepository(void) override = default;
        virtual void create(const Resource &item) override;
        virtual void update(const Resource &item) override;
        virtual void erase(const Resource &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<Resource>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<Resource>> getAll(void) override;

    private:
        MockGenericTimeChangeableRepository<Resource> impl;
};

#endif

