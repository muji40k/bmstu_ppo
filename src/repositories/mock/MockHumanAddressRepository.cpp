#include "MockHumanAddressRepository.h"

void MockHumanAddressRepository::create(const HumanAddress &item)
{
    this->impl.create(item);
}

void MockHumanAddressRepository::update(const HumanAddress &item)
{
    this->impl.update(item);
}

void MockHumanAddressRepository::erase(const HumanAddress &item)
{
    this->impl.erase(item);
}

void MockHumanAddressRepository::erase(const ICriteria &criteria)
{
    this->impl.erase(criteria);
}

std::shared_ptr<ITimeChangeableRepositorySet<HumanAddress>> MockHumanAddressRepository::get(const ICriteria &criteria)
{
    return this->impl.get(criteria);
}

std::shared_ptr<ITimeChangeableRepositorySet<HumanAddress>> MockHumanAddressRepository::getAll(void)
{
    return this->impl.getAll();
}

