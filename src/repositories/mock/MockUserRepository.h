#ifndef _MOCKUSERREPOSITORY_H_
#define _MOCKUSERREPOSITORY_H_

#include "IUserRepository.h"
#include "MockGenericRepository.h"

class MockUserRepository : public IUserRepository
{
    public:
        virtual ~MockUserRepository(void) override = default;
        virtual void create(const User &item) override;
        virtual void update(const User &item) override;
        virtual void erase(const User &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<IRepositorySet<User>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<IRepositorySet<User>> getAll(void) override;

    private:
        MockGenericRepository<User> impl;
};

#endif

