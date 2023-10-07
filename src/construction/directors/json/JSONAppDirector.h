#ifndef _JSONAPPDIRECTOR_H_
#define _JSONAPPDIRECTOR_H_

#include <initializer_list>
#include <unordered_map>
#include <nlohmann/json.hpp>

#include "IAppDirector.h"
#include "IAppBuilder.h"

#include "JSONAppContextDirector.h"

class JSONAppDirector : public IAppDirector
{
    public:
        class Item
        {
            public:
                virtual ~Item(void) = default;
                virtual const std::string &type(void) const = 0;
                virtual std::shared_ptr<IAppBuilder> parse(const nlohmann::json &object) = 0;
        };

    public:
        JSONAppDirector(nlohmann::json object,  
                        std::shared_ptr<JSONAppContextDirector> app_director,
                        std::initializer_list<std::shared_ptr<Item>> list);
        virtual ~JSONAppDirector(void) override = default;
        virtual void construct(void) override;
        virtual std::shared_ptr<App> result(void) override;

    private:
        const nlohmann::json object;
        std::shared_ptr<JSONAppContextDirector> app_director;
        std::unordered_map<std::string, std::shared_ptr<Item>> parsers;
        std::shared_ptr<IAppBuilder> builder = nullptr;
};

class JSONTechUiAppPareser : public JSONAppDirector::Item
{
    public:
        virtual ~JSONTechUiAppPareser(void) override = default;
        virtual const std::string &type(void) const override;
        virtual std::shared_ptr<IAppBuilder> parse(const nlohmann::json &object) override;
};

#endif

