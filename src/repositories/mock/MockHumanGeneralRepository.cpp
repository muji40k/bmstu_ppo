#include "MockHumanGeneralRepository.h"

void MockHumanGeneralRepository::create(const HumanGeneral &item)
{
    this->impl.create(item);
}

void MockHumanGeneralRepository::update(const HumanGeneral &item)
{
    this->impl.update(item);
}

void MockHumanGeneralRepository::erase(const HumanGeneral &item)
{
    this->impl.erase(item);
}

void MockHumanGeneralRepository::erase(const ICriteria &criteria)
{
    this->impl.erase(criteria);
}

std::shared_ptr<ITimeChangeableRepositorySet<HumanGeneral>> MockHumanGeneralRepository::get(const ICriteria &criteria)
{
    return this->impl.get(criteria);
}

std::shared_ptr<ITimeChangeableRepositorySet<HumanGeneral>> MockHumanGeneralRepository::getAll(void)
{
    return this->impl.getAll();
}

