#include "MockHumanLanguageRepository.h"

void MockHumanLanguageRepository::create(const HumanLanguage &item)
{
    this->impl.create(item);
}

void MockHumanLanguageRepository::update(const HumanLanguage &item)
{
    this->impl.update(item);
}

void MockHumanLanguageRepository::erase(const HumanLanguage &item)
{
    this->impl.erase(item);
}

void MockHumanLanguageRepository::erase(const ICriteria &criteria)
{
    this->impl.erase(criteria);
}

std::shared_ptr<ITimeChangeableRepositorySet<HumanLanguage>> MockHumanLanguageRepository::get(const ICriteria &criteria)
{
    return this->impl.get(criteria);
}

std::shared_ptr<ITimeChangeableRepositorySet<HumanLanguage>> MockHumanLanguageRepository::getAll(void)
{
    return this->impl.getAll();
}

