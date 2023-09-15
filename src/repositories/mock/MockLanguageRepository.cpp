#include "MockLanguageRepository.h"

void MockLanguageRepository::create(const Language &item)
{
    this->impl.create(item);
}

void MockLanguageRepository::update(const Language &item)
{
    this->impl.update(item);
}

void MockLanguageRepository::erase(const Language &item)
{
    this->impl.erase(item);
}

void MockLanguageRepository::erase(const ICriteria &criteria)
{
    this->impl.erase(criteria);
}

std::shared_ptr<ITimeChangeableRepositorySet<Language>> MockLanguageRepository::get(const ICriteria &criteria)
{
    return this->impl.get(criteria);
}

std::shared_ptr<ITimeChangeableRepositorySet<Language>> MockLanguageRepository::getAll(void)
{
    return this->impl.getAll();
}

