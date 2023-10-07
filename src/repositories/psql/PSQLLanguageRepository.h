#ifndef _PSQLLANGUAGEREPOSITORY_H_
#define _PSQLLANGUAGEREPOSITORY_H_

#include <pqxx/pqxx>

#include "ILanguageRepository.h"
#include "ICriteriaVisitorResultBuilder.h"

class PSQLLanguageRepository: public ILanguageRepository
{
    public:
        PSQLLanguageRepository(std::shared_ptr<pqxx::connection> connection,
                              std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder);
        virtual ~PSQLLanguageRepository(void) override = default;
        virtual void create(const Language &item) override;
        virtual void update(const Language &item) override;
        virtual void erase(const Language &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<Language>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<Language>> getAll(void) override;

    private:
        std::shared_ptr<pqxx::connection> connection;
        std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder;
};

#endif

