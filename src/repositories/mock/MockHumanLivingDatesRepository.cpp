#include "MockHumanLivingDatesRepository.h"

void MockHumanLivingDatesRepository::create(const HumanLivingDates &item)
{
    this->impl.create(item);
}

void MockHumanLivingDatesRepository::update(const HumanLivingDates &item)
{
    this->impl.update(item);
}

void MockHumanLivingDatesRepository::erase(const HumanLivingDates &item)
{
    this->impl.erase(item);
}

void MockHumanLivingDatesRepository::erase(const ICriteria &criteria)
{
    this->impl.erase(criteria);
}

std::shared_ptr<ITimeChangeableRepositorySet<HumanLivingDates>> MockHumanLivingDatesRepository::get(const ICriteria &criteria)
{
    return this->impl.get(criteria);
}

std::shared_ptr<ITimeChangeableRepositorySet<HumanLivingDates>> MockHumanLivingDatesRepository::getAll(void)
{
    return this->impl.getAll();
}

