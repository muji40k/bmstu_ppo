#include "MockHumanSocialRepository.h"

void MockHumanSocialRepository::create(const HumanSocial &item)
{
    this->impl.create(item);
}

void MockHumanSocialRepository::update(const HumanSocial &item)
{
    this->impl.update(item);
}

void MockHumanSocialRepository::erase(const HumanSocial &item)
{
    this->impl.erase(item);
}

void MockHumanSocialRepository::erase(const ICriteria &criteria)
{
    this->impl.erase(criteria);
}

std::shared_ptr<ITimeChangeableRepositorySet<HumanSocial>> MockHumanSocialRepository::get(const ICriteria &criteria)
{
    return this->impl.get(criteria);
}

std::shared_ptr<ITimeChangeableRepositorySet<HumanSocial>> MockHumanSocialRepository::getAll(void)
{
    return this->impl.getAll();
}

