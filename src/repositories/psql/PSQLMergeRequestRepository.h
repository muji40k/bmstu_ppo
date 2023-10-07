#ifndef _PSQLMERGEREQUESTREPOSITORY_H_
#define _PSQLMERGEREQUESTREPOSITORY_H_

#include <pqxx/pqxx>

#include "IMergeRequestRepository.h"
#include "ICriteriaVisitorResultBuilder.h"
#include "IHumanRepository.h"
#include "IUserRepository.h"

class PSQLMergeRequestRepository: public IMergeRequestRepository
{
    public:
        PSQLMergeRequestRepository(std::shared_ptr<pqxx::connection> connection,
                                   std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder,
                                   std::shared_ptr<IUserRepository> urepo,
                                   std::shared_ptr<IHumanRepository> hrepo);
        virtual ~PSQLMergeRequestRepository(void) override = default;
        virtual void create(const MergeRequest &item) override;
        virtual void update(const MergeRequest &item) override;
        virtual void erase(const MergeRequest &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<IRepositorySet<MergeRequest>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<IRepositorySet<MergeRequest>> getAll(void) override;

    private:
        std::shared_ptr<pqxx::connection> connection;
        std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder;
        std::shared_ptr<IUserRepository> urepo;
        std::shared_ptr<IHumanRepository> hrepo;
};

#endif

