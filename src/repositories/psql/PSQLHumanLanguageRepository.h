#ifndef _PSQLHUMANLANGUAGEREPOSITORY_H_
#define _PSQLHUMANLANGUAGEREPOSITORY_H_

#include <pqxx/pqxx>

#include "IHumanLanguageRepository.h"
#include "ICriteriaVisitorResultBuilder.h"
#include "ILanguageRepository.h"

class PSQLHumanLanguageRepository: public IHumanLanguageRepository
{
    public:
        PSQLHumanLanguageRepository(std::shared_ptr<pqxx::connection> connection,
                                    std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder,
                                    std::shared_ptr<ILanguageRepository> lrepo);
        virtual ~PSQLHumanLanguageRepository(void) override = default;
        virtual void create(const HumanLanguage &item) override;
        virtual void update(const HumanLanguage &item) override;
        virtual void erase(const HumanLanguage &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<HumanLanguage>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<HumanLanguage>> getAll(void) override;

    private:
        std::shared_ptr<pqxx::connection> connection;
        std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder;
        std::shared_ptr<ILanguageRepository> lrepo;
};

#endif

