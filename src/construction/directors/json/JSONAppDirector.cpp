#include "JSONAppDirector.h"

#include "TechUIAppBuilder.h"

JSONAppDirector::JSONAppDirector(nlohmann::json object,
                                 std::shared_ptr<JSONAppContextDirector> app_director,
                                 std::initializer_list<std::shared_ptr<Item>> list)
    : object(object), app_director(app_director)
{
    if (nullptr == object || nullptr == app_director)
        throw CALL_EX(NullptrAppDirectorException);

    for (auto item : list)
    {
        if (nullptr == item)
            throw CALL_EX(NullptrAppDirectorException);

        auto iter = this->parsers.find(item->type());

        if (this->parsers.end() == iter)
            this->parsers.emplace(item->type(), item);
        else
            (*iter).second = item;
    }
}

void JSONAppDirector::construct(void)
try
{
    std::string type = this->object["interface"];

    auto iter = this->parsers.find(type);

    if (this->parsers.end() == iter)
        throw CALL_EX(UnsupportedAppDirectorException);

    if (!this->object["interfaces"].contains(type))
        throw CALL_EX(WrongConfigurationAppDirectorException);

    this->builder = (*iter).second->parse(this->object["interfaces"][type]);
    this->app_director->construct();
    this->builder->setAppContext(this->app_director->result());
    this->builder->build();
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationAppContextDirectorException);
}
catch (nlohmann::json::exception &er)
{
    throw CALL_EX_MSG(WrongConfigurationAppContextDirectorException, er.what());
}

std::shared_ptr<App> JSONAppDirector::result(void)
{
    if (nullptr == this->builder)
        throw CALL_EX(NotReadyAppDirectorException);

    return this->builder->result();
}

const std::string &JSONTechUiAppPareser::type(void) const
{
    static const std::string type = "tui";

    return type;
}

std::shared_ptr<IAppBuilder> JSONTechUiAppPareser::parse(const nlohmann::json &)
{
    return std::make_shared<TechUIAppBuilder>();
}

