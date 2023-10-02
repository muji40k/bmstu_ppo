#ifndef _PSQLPLACERESOURCEREPOSITORY_H_
#define _PSQLPLACERESOURCEREPOSITORY_H_

#include <pqxx/pqxx>

#include "IPlaceResourceRepository.h"
#include "ICriteriaVisitorResultBuilder.h"
#include "IResourceRepository.h"

class PSQLPlaceResourceRepository: public IPlaceResourceRepository
{
    public:
        PSQLPlaceResourceRepository(std::shared_ptr<pqxx::connection> connection,
                                    std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder,
                                    std::shared_ptr<IResourceRepository> rrepo);
        virtual ~PSQLPlaceResourceRepository(void) override = default;
        virtual void create(const PlaceResource &item) override;
        virtual void update(const PlaceResource &item) override;
        virtual void erase(const PlaceResource &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<PlaceResource>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<PlaceResource>> getAll(void) override;

    private:
        std::shared_ptr<pqxx::connection> connection;
        std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder;
        std::shared_ptr<IResourceRepository> rrepo;
};

#endif

