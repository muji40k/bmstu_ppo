#ifndef _MOCKHUMANADDRESSREPOSITORY_H_
#define _MOCKHUMANADDRESSREPOSITORY_H_

#include "IHumanAddressRepository.h"
#include "MockGenericTimeChangeableRepository.h"

class MockHumanAddressRepository : public IHumanAddressRepository
{
    public:
        virtual ~MockHumanAddressRepository(void) override = default;
        virtual void create(const HumanAddress &item) override;
        virtual void update(const HumanAddress &item) override;
        virtual void erase(const HumanAddress &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<HumanAddress>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<HumanAddress>> getAll(void) override;

    private:
        MockGenericTimeChangeableRepository<HumanAddress> impl;
};

#endif

