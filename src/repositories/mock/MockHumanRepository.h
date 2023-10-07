#ifndef _MOCKHUMANREPOSITORY_H_
#define _MOCKHUMANREPOSITORY_H_

#include "IHumanRepository.h"
#include "MockGenericTimeChangeableRepository.h"

class MockHumanRepository : public IHumanRepository
{
    public:
        virtual ~MockHumanRepository(void) override = default;
        virtual void create(const Human &item) override;
        virtual void update(const Human &item) override;
        virtual void erase(const Human &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<Human>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<Human>> getAll(void) override;

    private:
        MockGenericTimeChangeableRepository<Human> impl;
};

#endif

