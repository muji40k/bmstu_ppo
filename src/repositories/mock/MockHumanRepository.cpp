#include "MockHumanRepository.h"

void MockHumanRepository::create(const Human &item)
{
    this->impl.create(item);
}

void MockHumanRepository::update(const Human &item)
{
    this->impl.update(item);
}

void MockHumanRepository::erase(const Human &item)
{
    this->impl.erase(item);
}

void MockHumanRepository::erase(const ICriteria &criteria)
{
    this->impl.erase(criteria);
}

std::shared_ptr<ITimeChangeableRepositorySet<Human>> MockHumanRepository::get(const ICriteria &criteria)
{
    return this->impl.get(criteria);
}

std::shared_ptr<ITimeChangeableRepositorySet<Human>> MockHumanRepository::getAll(void)
{
    return this->impl.getAll();
}

