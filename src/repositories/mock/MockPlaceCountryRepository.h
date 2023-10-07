#ifndef _MOCKPLACECOUNTRYREPOSITORY_H_
#define _MOCKPLACECOUNTRYREPOSITORY_H_

#include "IPlaceCountryRepository.h"
#include "MockGenericTimeChangeableRepository.h"

class MockPlaceCountryRepository : public IPlaceCountryRepository
{
    public:
        virtual ~MockPlaceCountryRepository(void) override = default;
        virtual void create(const PlaceCountry &item) override;
        virtual void update(const PlaceCountry &item) override;
        virtual void erase(const PlaceCountry &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<PlaceCountry>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<PlaceCountry>> getAll(void) override;

    private:
        MockGenericTimeChangeableRepository<PlaceCountry> impl;
};

#endif

