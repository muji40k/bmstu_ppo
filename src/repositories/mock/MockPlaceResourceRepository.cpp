#include "MockPlaceResourceRepository.h"

void MockPlaceResourceRepository::create(const PlaceResource &item)
{
    this->impl.create(item);
}

void MockPlaceResourceRepository::update(const PlaceResource &item)
{
    this->impl.update(item);
}

void MockPlaceResourceRepository::erase(const PlaceResource &item)
{
    this->impl.erase(item);
}

void MockPlaceResourceRepository::erase(const ICriteria &criteria)
{
    this->impl.erase(criteria);
}

std::shared_ptr<ITimeChangeableRepositorySet<PlaceResource>> MockPlaceResourceRepository::get(const ICriteria &criteria)
{
    return this->impl.get(criteria);
}

std::shared_ptr<ITimeChangeableRepositorySet<PlaceResource>> MockPlaceResourceRepository::getAll(void)
{
    return this->impl.getAll();
}

