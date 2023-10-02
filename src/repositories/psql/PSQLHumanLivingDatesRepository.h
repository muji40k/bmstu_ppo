#ifndef _PSQLHUMANLIVINGDATESREPOSITORY_H_
#define _PSQLHUMANLIVINGDATESREPOSITORY_H_

#include <pqxx/pqxx>

#include "IHumanLivingDatesRepository.h"
#include "ICriteriaVisitorResultBuilder.h"

class PSQLHumanLivingDatesRepository: public IHumanLivingDatesRepository
{
    public:
        PSQLHumanLivingDatesRepository(std::shared_ptr<pqxx::connection> connection,
                              std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder);
        virtual ~PSQLHumanLivingDatesRepository(void) override = default;
        virtual void create(const HumanLivingDates &item) override;
        virtual void update(const HumanLivingDates &item) override;
        virtual void erase(const HumanLivingDates &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<HumanLivingDates>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<HumanLivingDates>> getAll(void) override;

    private:
        std::shared_ptr<pqxx::connection> connection;
        std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder;
};

#endif

