#ifndef _MOCKPLACERESOURCEREPOSITORY_H_
#define _MOCKPLACERESOURCEREPOSITORY_H_

#include "IPlaceResourceRepository.h"
#include "MockGenericTimeChangeableRepository.h"

class MockPlaceResourceRepository : public IPlaceResourceRepository
{
    public:
        virtual ~MockPlaceResourceRepository(void) override = default;
        virtual void create(const PlaceResource &item) override;
        virtual void update(const PlaceResource &item) override;
        virtual void erase(const PlaceResource &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<PlaceResource>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<PlaceResource>> getAll(void) override;

    private:
        MockGenericTimeChangeableRepository<PlaceResource> impl;
};

#endif

