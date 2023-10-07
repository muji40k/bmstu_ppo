#ifndef _PSQLCOUNTRYREPOSITORY_H_
#define _PSQLCOUNTRYREPOSITORY_H_

#include <pqxx/pqxx>

#include "ICountryRepository.h"
#include "ICriteriaVisitorResultBuilder.h"

class PSQLCountryRepository: public ICountryRepository
{
    public:
        PSQLCountryRepository(std::shared_ptr<pqxx::connection> connection,
                              std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder);
        virtual ~PSQLCountryRepository(void) override = default;
        virtual void create(const Country &item) override;
        virtual void update(const Country &item) override;
        virtual void erase(const Country &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<Country>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<Country>> getAll(void) override;

    private:
        std::shared_ptr<pqxx::connection> connection;
        std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder;
};

#endif

