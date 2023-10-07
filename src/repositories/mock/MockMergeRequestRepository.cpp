#include "MockMergeRequestRepository.h"

void MockMergeRequestRepository::create(const MergeRequest &item)
{
    this->impl.create(item);
}

void MockMergeRequestRepository::update(const MergeRequest &item)
{
    this->impl.update(item);
}

void MockMergeRequestRepository::erase(const MergeRequest &item)
{
    this->impl.erase(item);
}

void MockMergeRequestRepository::erase(const ICriteria &criteria)
{
    this->impl.erase(criteria);
}

std::shared_ptr<IRepositorySet<MergeRequest>> MockMergeRequestRepository::get(const ICriteria &criteria)
{
    return this->impl.get(criteria);
}

std::shared_ptr<IRepositorySet<MergeRequest>> MockMergeRequestRepository::getAll(void)
{
    return this->impl.getAll();
}

