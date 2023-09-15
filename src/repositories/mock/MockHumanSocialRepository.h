#ifndef _MOCKHUMANSOCIALREPOSITORY_H_
#define _MOCKHUMANSOCIALREPOSITORY_H_

#include "IHumanSocialRepository.h"
#include "MockGenericTimeChangeableRepository.h"

class MockHumanSocialRepository : public IHumanSocialRepository
{
    public:
        virtual ~MockHumanSocialRepository(void) override = default;
        virtual void create(const HumanSocial &item) override;
        virtual void update(const HumanSocial &item) override;
        virtual void erase(const HumanSocial &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<HumanSocial>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<HumanSocial>> getAll(void) override;

    private:
        MockGenericTimeChangeableRepository<HumanSocial> impl;
};

#endif

