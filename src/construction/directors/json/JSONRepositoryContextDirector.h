#ifndef _JSONREPOSITORYCONTEXTDIRECTOR_H_
#define _JSONREPOSITORYCONTEXTDIRECTOR_H_

#include <initializer_list>
#include <unordered_map>
#include <nlohmann/json.hpp>

#include "IRepositoryContextDirector.h"
#include "IRepositoryContextBuilder.h"

class JSONRepositoryContextDirector : public IRepositoryContextDirector
{
    public:
        class Item
        {
            public:
                virtual ~Item(void) = default;
                virtual const std::string &type(void) const = 0;
                virtual std::shared_ptr<IRepositoryContextBuilder> parse(const nlohmann::json &object) = 0;
        };

    public:
        JSONRepositoryContextDirector(nlohmann::json object, std::initializer_list<std::shared_ptr<Item>> list);
        virtual ~JSONRepositoryContextDirector(void) override = default;
        virtual void construct(void) override;
        virtual std::shared_ptr<RepositoryContext> result(void) override;
        virtual const std::list<std::shared_ptr<RegistrationHook::Item>> &registrationHooks(void) override;
        virtual const std::list<std::shared_ptr<AuthorizationHook::Item>> &authorizationHooks(void) override;

    private:
        const nlohmann::json object;
        std::unordered_map<std::string, std::shared_ptr<Item>> parsers;
        std::shared_ptr<IRepositoryContextBuilder> builder = nullptr;
};

class JSONPSQLRepositoryContextPareser : public JSONRepositoryContextDirector::Item
{
    public:
        virtual ~JSONPSQLRepositoryContextPareser(void) override = default;
        virtual const std::string &type(void) const override;
        virtual std::shared_ptr<IRepositoryContextBuilder> parse(const nlohmann::json &object) override;
};

#endif

