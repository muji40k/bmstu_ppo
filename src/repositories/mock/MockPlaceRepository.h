#ifndef _MOCKPLACEREPOSITORY_H_
#define _MOCKPLACEREPOSITORY_H_

#include "IPlaceRepository.h"
#include "MockGenericTimeChangeableRepository.h"

class MockPlaceRepository : public IPlaceRepository
{
    public:
        virtual ~MockPlaceRepository(void) override = default;
        virtual void create(const Place &item) override;
        virtual void update(const Place &item) override;
        virtual void erase(const Place &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<Place>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<Place>> getAll(void) override;

    private:
        MockGenericTimeChangeableRepository<Place> impl;
};

#endif

