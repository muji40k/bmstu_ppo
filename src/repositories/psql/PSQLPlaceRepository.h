#ifndef _PSQLPLACEREPOSITORY_H_
#define _PSQLPLACEREPOSITORY_H_

#include <pqxx/pqxx>

#include "IPlaceRepository.h"
#include "ICriteriaVisitorResultBuilder.h"

class PSQLPlaceRepository: public IPlaceRepository
{
    public:
        PSQLPlaceRepository(std::shared_ptr<pqxx::connection> connection,
                              std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder);
        virtual ~PSQLPlaceRepository(void) override = default;
        virtual void create(const Place &item) override;
        virtual void update(const Place &item) override;
        virtual void erase(const Place &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<Place>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<Place>> getAll(void) override;

    private:
        std::shared_ptr<pqxx::connection> connection;
        std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder;
};

#endif

