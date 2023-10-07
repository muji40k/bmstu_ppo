#include "MockUserHumanRepository.h"

void MockUserHumanRepository::create(const UserHuman &item)
{
    this->impl.create(item);
}

void MockUserHumanRepository::update(const UserHuman &item)
{
    this->impl.update(item);
}

void MockUserHumanRepository::erase(const UserHuman &item)
{
    this->impl.erase(item);
}

void MockUserHumanRepository::erase(const ICriteria &criteria)
{
    this->impl.erase(criteria);
}

std::shared_ptr<IRepositorySet<UserHuman>> MockUserHumanRepository::get(const ICriteria &criteria)
{
    return this->impl.get(criteria);
}

std::shared_ptr<IRepositorySet<UserHuman>> MockUserHumanRepository::getAll(void)
{
    return this->impl.getAll();
}

