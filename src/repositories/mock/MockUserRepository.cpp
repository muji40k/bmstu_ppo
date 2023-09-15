#include "MockUserRepository.h"

void MockUserRepository::create(const User &item)
{
    this->impl.create(item);
}

void MockUserRepository::update(const User &item)
{
    this->impl.update(item);
}

void MockUserRepository::erase(const User &item)
{
    this->impl.erase(item);
}

void MockUserRepository::erase(const ICriteria &criteria)
{
    this->impl.erase(criteria);
}

std::shared_ptr<IRepositorySet<User>> MockUserRepository::get(const ICriteria &criteria)
{
    return this->impl.get(criteria);
}

std::shared_ptr<IRepositorySet<User>> MockUserRepository::getAll(void)
{
    return this->impl.getAll();
}

