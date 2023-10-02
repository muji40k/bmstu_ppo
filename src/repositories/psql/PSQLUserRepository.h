#ifndef _PSQLUSERREPOSITORY_H_
#define _PSQLUSERREPOSITORY_H_

#include <pqxx/pqxx>

#include "IUserRepository.h"
#include "ICriteriaVisitorResultBuilder.h"

class PSQLUserRepository: public IUserRepository
{
    public:
        PSQLUserRepository(std::shared_ptr<pqxx::connection> connection,
                              std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder);
        virtual ~PSQLUserRepository(void) override = default;
        virtual void create(const User &item) override;
        virtual void update(const User &item) override;
        virtual void erase(const User &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<IRepositorySet<User>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<IRepositorySet<User>> getAll(void) override;

    private:
        std::shared_ptr<pqxx::connection> connection;
        std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder;
};

#endif

