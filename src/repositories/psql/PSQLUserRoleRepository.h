#ifndef _PSQLUSERROLEREPOSITORY_H_
#define _PSQLUSERROLEREPOSITORY_H_

#include <pqxx/pqxx>

#include "IUserRoleRepository.h"
#include "ICriteriaVisitorResultBuilder.h"

class PSQLUserRoleRepository: public IUserRoleRepository
{
    public:
        PSQLUserRoleRepository(std::shared_ptr<pqxx::connection> connection,
                              std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder);
        virtual ~PSQLUserRoleRepository(void) override = default;
        virtual void create(const UserRole &item) override;
        virtual void update(const UserRole &item) override;
        virtual void erase(const UserRole &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<IRepositorySet<UserRole>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<IRepositorySet<UserRole>> getAll(void) override;

    private:
        std::shared_ptr<pqxx::connection> connection;
        std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder;
};

#endif

