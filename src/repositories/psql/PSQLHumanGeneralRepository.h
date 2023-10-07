#ifndef _PSQLHUMANGENERALREPOSITORY_H_
#define _PSQLHUMANGENERALREPOSITORY_H_

#include <pqxx/pqxx>

#include "IHumanGeneralRepository.h"
#include "ICriteriaVisitorResultBuilder.h"

class PSQLHumanGeneralRepository: public IHumanGeneralRepository
{
    public:
        PSQLHumanGeneralRepository(std::shared_ptr<pqxx::connection> connection,
                              std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder);
        virtual ~PSQLHumanGeneralRepository(void) override = default;
        virtual void create(const HumanGeneral &item) override;
        virtual void update(const HumanGeneral &item) override;
        virtual void erase(const HumanGeneral &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<HumanGeneral>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<HumanGeneral>> getAll(void) override;

    private:
        std::shared_ptr<pqxx::connection> connection;
        std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder;
};

#endif

