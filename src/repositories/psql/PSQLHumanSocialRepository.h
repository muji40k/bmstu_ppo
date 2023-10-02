#ifndef _PSQLHUMANSOCIALREPOSITORY_H_
#define _PSQLHUMANSOCIALREPOSITORY_H_

#include <pqxx/pqxx>

#include "IHumanSocialRepository.h"
#include "ICriteriaVisitorResultBuilder.h"

class PSQLHumanSocialRepository: public IHumanSocialRepository
{
    public:
        PSQLHumanSocialRepository(std::shared_ptr<pqxx::connection> connection,
                              std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder);
        virtual ~PSQLHumanSocialRepository(void) override = default;
        virtual void create(const HumanSocial &item) override;
        virtual void update(const HumanSocial &item) override;
        virtual void erase(const HumanSocial &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<HumanSocial>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<HumanSocial>> getAll(void) override;

    private:
        std::shared_ptr<pqxx::connection> connection;
        std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder;
};

#endif

