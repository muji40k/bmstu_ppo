#include "MockResourceRepository.h"

void MockResourceRepository::create(const Resource &item)
{
    this->impl.create(item);
}

void MockResourceRepository::update(const Resource &item)
{
    this->impl.update(item);
}

void MockResourceRepository::erase(const Resource &item)
{
    this->impl.erase(item);
}

void MockResourceRepository::erase(const ICriteria &criteria)
{
    this->impl.erase(criteria);
}

std::shared_ptr<ITimeChangeableRepositorySet<Resource>> MockResourceRepository::get(const ICriteria &criteria)
{
    return this->impl.get(criteria);
}

std::shared_ptr<ITimeChangeableRepositorySet<Resource>> MockResourceRepository::getAll(void)
{
    return this->impl.getAll();
}

