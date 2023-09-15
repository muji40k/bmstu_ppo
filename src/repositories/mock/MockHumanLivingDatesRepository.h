#ifndef _MOCKHUMANLIVINGDATESREPOSITORY_H_
#define _MOCKHUMANLIVINGDATESREPOSITORY_H_

#include "IHumanLivingDatesRepository.h"
#include "MockGenericTimeChangeableRepository.h"

class MockHumanLivingDatesRepository : public IHumanLivingDatesRepository
{
    public:
        virtual ~MockHumanLivingDatesRepository(void) override = default;
        virtual void create(const HumanLivingDates &item) override;
        virtual void update(const HumanLivingDates &item) override;
        virtual void erase(const HumanLivingDates &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<HumanLivingDates>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<HumanLivingDates>> getAll(void) override;

    private:
        MockGenericTimeChangeableRepository<HumanLivingDates> impl;
};

#endif

