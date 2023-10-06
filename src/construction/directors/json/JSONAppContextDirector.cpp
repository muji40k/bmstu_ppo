#include "JSONAppContextDirector.h"

#include "PlainAppContextBuilder.h"
#include "LogAppContextBuilder.h"
#include "FileLogger.h"

JSONAppContextDirector::JSONAppContextDirector(nlohmann::json object,
                                               std::shared_ptr<JSONRepositoryContextDirector> repo_director,
                                               std::initializer_list<std::shared_ptr<Item>> list)
    : object(object), repo_director(repo_director)
{
    if (nullptr == object || nullptr == repo_director)
        throw CALL_EX(NullptrAppContextDirectorException);

    for (auto item : list)
    {
        if (nullptr == item)
            throw CALL_EX(NullptrAppContextDirectorException);

        auto iter = this->parsers.find(item->type());

        if (this->parsers.end() == iter)
            this->parsers.emplace(item->type(), item);
        else
            (*iter).second = item;
    }
}

void JSONAppContextDirector::construct(void)
try
{
    std::string type = this->object["implementation"];

    auto iter = this->parsers.find(type);

    if (this->parsers.end() == iter)
        throw CALL_EX(UnsupportedAppContextDirectorException);

    if (!this->object["implementations"].contains(type))
        throw CALL_EX(WrongConfigurationAppContextDirectorException);

    this->builder = (*iter).second->parse(this->object["implementations"][type]);
    this->repo_director->construct();
    this->builder->setAuthorizationHooks(this->repo_director->authorizationHooks());
    this->builder->setRegistrationHooks(this->repo_director->registrationHooks());
    this->builder->setRepositoryContext(this->repo_director->result());
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

std::shared_ptr<AppContext> JSONAppContextDirector::result(void)
{
    if (nullptr == this->builder)
        throw CALL_EX(NotReadyAppContextDirectorException);

    return this->builder->result();
}

const std::string &JSONPlainAppContextPareser::type(void) const
{
    static const std::string type = "plain";

    return type;
}

std::shared_ptr<IAppContextBuilder> JSONPlainAppContextPareser::parse(const nlohmann::json &)
{
    return std::make_shared<PlainAppContextBuilder>();
}

const std::string &JSONLogAppContextPareser::type(void) const
{
    static const std::string type = "logged";

    return type;
}

class FileLoggerCreator : public LogAppContextBuilder::LoggerCreator
{
    public:
        FileLoggerCreator(std::string filename, ILogger::Levels limit=ILogger::ALL)
            : filename(filename), limit(limit) {}
        virtual ~FileLoggerCreator(void) override = default;
        virtual std::shared_ptr<ILogger> create(void) override
        {
            return std::make_shared<FileLogger>(filename, limit);
        }

    private:
        const std::string filename;
        const ILogger::Levels limit;
};

std::shared_ptr<IAppContextBuilder> JSONLogAppContextPareser::parse(const nlohmann::json &object)
{
    static const std::unordered_map<std::string, ILogger::Levels> levels =
    {
        {"service", ILogger::SERVICE},
        {"error", ILogger::ERROR},
        {"warning", ILogger::WARNING},
        {"info", ILogger::INFO},
        {"debug", ILogger::DEBUG},
        {"all", ILogger::ALL}
    };

    std::string level = object["level"],
                filename = object["file"];

    auto builder = std::make_shared<LogAppContextBuilder>();

    builder->setLoggerCreator(std::make_shared<FileLoggerCreator>(filename, levels.at(level)));

    return builder;
}

