#ifndef _PSQLUSERHUMANREPOSITORY_H_
#define _PSQLUSERHUMANREPOSITORY_H_

#include <pqxx/pqxx>

#include "IHumanRepository.h"
#include "IUserHumanRepository.h"
#include "ICriteriaVisitorResultBuilder.h"

class PSQLUserHumanRepository: public IUserHumanRepository
{
    public:
        PSQLUserHumanRepository(std::shared_ptr<pqxx::connection> connection,
                                std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder,
                                std::shared_ptr<IHumanRepository> repo);
        virtual ~PSQLUserHumanRepository(void) override = default;
        virtual void create(const UserHuman &item) override;
        virtual void update(const UserHuman &item) override;
        virtual void erase(const UserHuman &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<IRepositorySet<UserHuman>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<IRepositorySet<UserHuman>> getAll(void) override;

    private:
        std::shared_ptr<pqxx::connection> connection;
        std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder;
        std::shared_ptr<IHumanRepository> repo;
};

#endif

