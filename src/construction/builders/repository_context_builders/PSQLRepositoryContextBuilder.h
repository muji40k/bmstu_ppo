#ifndef _PSQLREPOSITORYCONTEXTBUILDER_H_
#define _PSQLREPOSITORYCONTEXTBUILDER_H_

#include <unordered_map>

#include <pqxx/pqxx>

#include "IRepositoryContextBuilder.h"
#include "CriteriaValueStringConverter.h"

class PSQLRepositoryContextBuilder : public IRepositoryContextBuilder
{
    public:
        virtual ~PSQLRepositoryContextBuilder(void) override = default;
        virtual void build(void) override;
        virtual std::shared_ptr<RepositoryContext> result(void) override;
        virtual const std::list<std::shared_ptr<RegistrationHook::Item>> &registrationHooks(void) override;
        virtual const std::list<std::shared_ptr<AuthorizationHook::Item>> &authorizationHooks(void) override;

        void setConnectionString(std::string conn);
        void setTimeZone(std::string tz);

    private:
        std::shared_ptr<pqxx::connection> getConnection(void) const;

    private:
        bool ready = false;
        std::string connection_string;
        std::string timezone;
        std::shared_ptr<RepositoryContext> context_result = nullptr;
        std::list<std::shared_ptr<RegistrationHook::Item>> registration_hooks;
        std::list<std::shared_ptr<AuthorizationHook::Item>> authorization_hooks;

        static const std::unordered_map<std::string, std::string> map;
        static const std::list<std::shared_ptr<CriteriaValueStringConverter::Item>> converters;
};

#endif

