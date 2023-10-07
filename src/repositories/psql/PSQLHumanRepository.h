#ifndef _PSQLHUMANREPOSITORY_H_
#define _PSQLHUMANREPOSITORY_H_

#include <pqxx/pqxx>

#include "IHumanRepository.h"
#include "ICriteriaVisitorResultBuilder.h"

class PSQLHumanRepository: public IHumanRepository
{
    public:
        PSQLHumanRepository(std::shared_ptr<pqxx::connection> connection,
                              std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder);
        virtual ~PSQLHumanRepository(void) override = default;
        virtual void create(const Human &item) override;
        virtual void update(const Human &item) override;
        virtual void erase(const Human &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<Human>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<Human>> getAll(void) override;

    private:
        std::shared_ptr<pqxx::connection> connection;
        std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder;
};

#endif

