#ifndef _MOCKHUMANGENERALREPOSITORY_H_
#define _MOCKHUMANGENERALREPOSITORY_H_

#include "IHumanGeneralRepository.h"
#include "MockGenericTimeChangeableRepository.h"

class MockHumanGeneralRepository : public IHumanGeneralRepository
{
    public:
        virtual ~MockHumanGeneralRepository(void) override = default;
        virtual void create(const HumanGeneral &item) override;
        virtual void update(const HumanGeneral &item) override;
        virtual void erase(const HumanGeneral &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<HumanGeneral>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<HumanGeneral>> getAll(void) override;

    private:
        MockGenericTimeChangeableRepository<HumanGeneral> impl;
};

#endif

