#ifndef _PSQLHUMANADDRESSREPOSITORY_H_
#define _PSQLHUMANADDRESSREPOSITORY_H_

#include <pqxx/pqxx>

#include "IHumanAddressRepository.h"
#include "ICriteriaVisitorResultBuilder.h"

class PSQLHumanAddressRepository: public IHumanAddressRepository
{
    public:
        PSQLHumanAddressRepository(std::shared_ptr<pqxx::connection> connection,
                              std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder);
        virtual ~PSQLHumanAddressRepository(void) override = default;
        virtual void create(const HumanAddress &item) override;
        virtual void update(const HumanAddress &item) override;
        virtual void erase(const HumanAddress &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<HumanAddress>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<HumanAddress>> getAll(void) override;

    private:
        std::shared_ptr<pqxx::connection> connection;
        std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder;
};

#endif

