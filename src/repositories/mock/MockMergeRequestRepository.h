#ifndef _MOCKMERGEREQUESTREPOSITORY_H_
#define _MOCKMERGEREQUESTREPOSITORY_H_

#include "IMergeRequestRepository.h"
#include "MockGenericRepository.h"

class MockMergeRequestRepository : public IMergeRequestRepository
{
    public:
        virtual ~MockMergeRequestRepository(void) override = default;
        virtual void create(const MergeRequest &item) override;
        virtual void update(const MergeRequest &item) override;
        virtual void erase(const MergeRequest &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<IRepositorySet<MergeRequest>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<IRepositorySet<MergeRequest>> getAll(void) override;

    private:
        MockGenericRepository<MergeRequest> impl;
};

#endif

