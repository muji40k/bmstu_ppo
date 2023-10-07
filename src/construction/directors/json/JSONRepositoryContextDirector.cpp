#include "JSONRepositoryContextDirector.h"

#include "PSQLRepositoryContextBuilder.h"

JSONRepositoryContextDirector::JSONRepositoryContextDirector(nlohmann::json object, std::initializer_list<std::shared_ptr<Item>> list)
    : object(object)
{
    if (nullptr == object)
        throw CALL_EX(NullptrRepositoryContextDirectorException);

    for (auto item : list)
    {
        if (nullptr == item)
            throw CALL_EX(NullptrRepositoryContextDirectorException);

        auto iter = this->parsers.find(item->type());

        if (this->parsers.end() == iter)
            this->parsers.emplace(item->type(), item);
        else
            (*iter).second = item;
    }
}

void JSONRepositoryContextDirector::construct(void)
try
{
    std::string type = this->object["connection"];

    auto iter = this->parsers.find(type);

    if (this->parsers.end() == iter)
        throw CALL_EX(UnsupportedRepositoryContextDirectorException);

    if (!this->object["connections"].contains(type))
        throw CALL_EX(WrongConfigurationRepositoryContextDirectorException);

    this->builder = (*iter).second->parse(this->object["connections"][type]);
    this->builder->build();
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationRepositoryContextDirectorException);
}
catch (nlohmann::json::exception &er)
{
    throw CALL_EX_MSG(WrongConfigurationRepositoryContextDirectorException, er.what());
}

std::shared_ptr<RepositoryContext> JSONRepositoryContextDirector::result(void)
{
    if (nullptr == this->builder)
        throw CALL_EX(NotReadyRepositoryContextDirectorException);

    return this->builder->result();
}

const std::list<std::shared_ptr<RegistrationHook::Item>> &JSONRepositoryContextDirector::registrationHooks(void)
{
    if (nullptr == this->builder)
        throw CALL_EX(NotReadyRepositoryContextDirectorException);

    return this->builder->registrationHooks();
}

const std::list<std::shared_ptr<AuthorizationHook::Item>> &JSONRepositoryContextDirector::authorizationHooks(void)
{
    if (nullptr == this->builder)
        throw CALL_EX(NotReadyRepositoryContextDirectorException);

    return this->builder->authorizationHooks();
}

const std::string &JSONPSQLRepositoryContextPareser::type(void) const
{
    static const std::string type = "psql";

    return type;
}

std::shared_ptr<IRepositoryContextBuilder> JSONPSQLRepositoryContextPareser::parse(const nlohmann::json &object)
{
    std::string connstring = "user=" + object["user"].get<std::string>() + " "
                             "host=" + object["host"].get<std::string>() + " "
                             "password=" + object["password"].get<std::string>() + " "
                             "dbname=" + object["dbname"].get<std::string>() + " "
                             "port=" + std::to_string(object["port"].get<int>());

    auto builder = std::make_shared<PSQLRepositoryContextBuilder>();
    builder->setConnectionString(connstring);

    if (object.contains("timezone"))
        builder->setTimeZone(object["timezone"]);

    return builder;
}

