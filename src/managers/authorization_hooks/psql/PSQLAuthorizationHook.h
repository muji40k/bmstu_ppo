#ifndef _PSQLAUTHORIZATIONHOOK_H_
#define _PSQLAUTHORIZATIONHOOK_H_

#include <memory>
#include <pqxx/pqxx>

#include "AuthorizationHook.h"

class PSQLAuthorizationHook : public AuthorizationHook::Item
{
    public:
        PSQLAuthorizationHook(std::shared_ptr<pqxx::connection> connection);
        virtual ~PSQLAuthorizationHook(void) override = default;
        virtual bool perform(RepositoryContext &context, const User &user,
                             const std::string &name) override;

    private:
        std::shared_ptr<pqxx::connection> connection;
};

#endif

