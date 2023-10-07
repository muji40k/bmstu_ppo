#ifndef _PSQLRESOURCEREPOSITORY_H_
#define _PSQLRESOURCEREPOSITORY_H_

#include <pqxx/pqxx>

#include "IResourceRepository.h"
#include "ICriteriaVisitorResultBuilder.h"

class PSQLResourceRepository: public IResourceRepository
{
    public:
        PSQLResourceRepository(std::shared_ptr<pqxx::connection> connection,
                              std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder);
        virtual ~PSQLResourceRepository(void) override = default;
        virtual void create(const Resource &item) override;
        virtual void update(const Resource &item) override;
        virtual void erase(const Resource &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<Resource>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<Resource>> getAll(void) override;

    private:
        std::shared_ptr<pqxx::connection> connection;
        std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder;
};

#endif

