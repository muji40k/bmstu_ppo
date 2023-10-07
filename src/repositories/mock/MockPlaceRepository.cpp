#include "MockPlaceRepository.h"

void MockPlaceRepository::create(const Place &item)
{
    this->impl.create(item);
}

void MockPlaceRepository::update(const Place &item)
{
    this->impl.update(item);
}

void MockPlaceRepository::erase(const Place &item)
{
    this->impl.erase(item);
}

void MockPlaceRepository::erase(const ICriteria &criteria)
{
    this->impl.erase(criteria);
}

std::shared_ptr<ITimeChangeableRepositorySet<Place>> MockPlaceRepository::get(const ICriteria &criteria)
{
    return this->impl.get(criteria);
}

std::shared_ptr<ITimeChangeableRepositorySet<Place>> MockPlaceRepository::getAll(void)
{
    return this->impl.getAll();
}

