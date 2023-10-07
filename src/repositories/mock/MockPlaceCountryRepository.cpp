#include "MockPlaceCountryRepository.h"

void MockPlaceCountryRepository::create(const PlaceCountry &item)
{
    this->impl.create(item);
}

void MockPlaceCountryRepository::update(const PlaceCountry &item)
{
    this->impl.update(item);
}

void MockPlaceCountryRepository::erase(const PlaceCountry &item)
{
    this->impl.erase(item);
}

void MockPlaceCountryRepository::erase(const ICriteria &criteria)
{
    this->impl.erase(criteria);
}

std::shared_ptr<ITimeChangeableRepositorySet<PlaceCountry>> MockPlaceCountryRepository::get(const ICriteria &criteria)
{
    return this->impl.get(criteria);
}

std::shared_ptr<ITimeChangeableRepositorySet<PlaceCountry>> MockPlaceCountryRepository::getAll(void)
{
    return this->impl.getAll();
}

