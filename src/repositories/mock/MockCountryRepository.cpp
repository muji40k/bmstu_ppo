#include "MockCountryRepository.h"

void MockCountryRepository::create(const Country &item)
{
    this->impl.create(item);
}

void MockCountryRepository::update(const Country &item)
{
    this->impl.update(item);
}

void MockCountryRepository::erase(const Country &item)
{
    this->impl.erase(item);
}

void MockCountryRepository::erase(const ICriteria &criteria)
{
    this->impl.erase(criteria);
}

std::shared_ptr<ITimeChangeableRepositorySet<Country>> MockCountryRepository::get(const ICriteria &criteria)
{
    return this->impl.get(criteria);
}

std::shared_ptr<ITimeChangeableRepositorySet<Country>> MockCountryRepository::getAll(void)
{
    return this->impl.getAll();
}

