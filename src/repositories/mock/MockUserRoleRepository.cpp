#include "MockUserRoleRepository.h"

void MockUserRoleRepository::create(const UserRole &item)
{
    this->impl.create(item);
}

void MockUserRoleRepository::update(const UserRole &item)
{
    this->impl.update(item);
}

void MockUserRoleRepository::erase(const UserRole &item)
{
    this->impl.erase(item);
}

void MockUserRoleRepository::erase(const ICriteria &criteria)
{
    this->impl.erase(criteria);
}

std::shared_ptr<IRepositorySet<UserRole>> MockUserRoleRepository::get(const ICriteria &criteria)
{
    return this->impl.get(criteria);
}

std::shared_ptr<IRepositorySet<UserRole>> MockUserRoleRepository::getAll(void)
{
    return this->impl.getAll();
}

