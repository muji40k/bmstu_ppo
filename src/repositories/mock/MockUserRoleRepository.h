#ifndef _MOCKUSERROLEREPOSITORY_H_
#define _MOCKUSERROLEREPOSITORY_H_

#include "IUserRoleRepository.h"
#include "MockGenericRepository.h"

class MockUserRoleRepository : public IUserRoleRepository
{
    public:
        virtual ~MockUserRoleRepository(void) override = default;
        virtual void create(const UserRole &item) override;
        virtual void update(const UserRole &item) override;
        virtual void erase(const UserRole &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<IRepositorySet<UserRole>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<IRepositorySet<UserRole>> getAll(void) override;

    private:
        MockGenericRepository<UserRole> impl;
};

#endif

