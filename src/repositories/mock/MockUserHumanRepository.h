#ifndef _MOCKUSERHUMANREPOSITORY_H_
#define _MOCKUSERHUMANREPOSITORY_H_

#include "IUserHumanRepository.h"
#include "MockGenericRepository.h"

class MockUserHumanRepository : public IUserHumanRepository
{
    public:
        virtual ~MockUserHumanRepository(void) override = default;
        virtual void create(const UserHuman &item) override;
        virtual void update(const UserHuman &item) override;
        virtual void erase(const UserHuman &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<IRepositorySet<UserHuman>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<IRepositorySet<UserHuman>> getAll(void) override;

    private:
        MockGenericRepository<UserHuman> impl;
};

#endif

