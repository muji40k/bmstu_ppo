#ifndef _JSONAPPCONTEXTDIRECTOR_H_
#define _JSONAPPCONTEXTDIRECTOR_H_

#include <initializer_list>
#include <unordered_map>
#include <nlohmann/json.hpp>

#include "IAppContextDirector.h"
#include "IAppContextBuilder.h"

#include "JSONRepositoryContextDirector.h"

class JSONAppContextDirector : public IAppContextDirector
{
    public:
        class Item
        {
            public:
                virtual ~Item(void) = default;
                virtual const std::string &type(void) const = 0;
                virtual std::shared_ptr<IAppContextBuilder> parse(const nlohmann::json &object) = 0;
        };

    public:
        JSONAppContextDirector(nlohmann::json object,
                               std::shared_ptr<JSONRepositoryContextDirector> repo_director,
                               std::initializer_list<std::shared_ptr<Item>> list);
        virtual ~JSONAppContextDirector(void) override = default;
        virtual void construct(void) override;
        virtual std::shared_ptr<AppContext> result(void) override;

    private:
        const nlohmann::json object;
        std::shared_ptr<JSONRepositoryContextDirector> repo_director;
        std::unordered_map<std::string, std::shared_ptr<Item>> parsers;
        std::shared_ptr<IAppContextBuilder> builder = nullptr;
};

class JSONPlainAppContextPareser : public JSONAppContextDirector::Item
{
    public:
        virtual ~JSONPlainAppContextPareser(void) override = default;
        virtual const std::string &type(void) const override;
        virtual std::shared_ptr<IAppContextBuilder> parse(const nlohmann::json &object) override;
};

class JSONLogAppContextPareser : public JSONAppContextDirector::Item
{
    public:
        virtual ~JSONLogAppContextPareser(void) override = default;
        virtual const std::string &type(void) const override;
        virtual std::shared_ptr<IAppContextBuilder> parse(const nlohmann::json &object) override;
};

#endif

