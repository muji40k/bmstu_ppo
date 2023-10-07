#ifndef _PSQLPLACECOUNTRYREPOSITORY_H_
#define _PSQLPLACECOUNTRYREPOSITORY_H_

#include <pqxx/pqxx>

#include "IPlaceCountryRepository.h"
#include "ICriteriaVisitorResultBuilder.h"

class PSQLPlaceCountryRepository: public IPlaceCountryRepository
{
    public:
        PSQLPlaceCountryRepository(std::shared_ptr<pqxx::connection> connection,
                              std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder);
        virtual ~PSQLPlaceCountryRepository(void) override = default;
        virtual void create(const PlaceCountry &item) override;
        virtual void update(const PlaceCountry &item) override;
        virtual void erase(const PlaceCountry &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<PlaceCountry>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<PlaceCountry>> getAll(void) override;

    private:
        std::shared_ptr<pqxx::connection> connection;
        std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder;
};

#endif

