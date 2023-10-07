#include <memory>
#include <fstream>

#include "PSQLRepositoryContextBuilder.h"
#include "LogAppContextBuilder.h"
#include "TechUIAppBuilder.h"

#include <nlohmann/json.hpp>
#include "JSONRepositoryContextDirector.h"
#include "JSONAppContextDirector.h"
#include "JSONAppDirector.h"

int main(int , char **)
{
    std::ifstream file;
    file.open("config.json", std::ios::in);
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    nlohmann::json object = nlohmann::json::parse(buffer.str());

    auto repo_context_director = std::make_shared<JSONRepositoryContextDirector>(object,
        std::initializer_list<std::shared_ptr<JSONRepositoryContextDirector::Item>>({std::make_shared<JSONPSQLRepositoryContextPareser>()}));
    auto app_context_director  = std::make_shared<JSONAppContextDirector>(object, repo_context_director,
        std::initializer_list<std::shared_ptr<JSONAppContextDirector::Item>>({std::make_shared<JSONPlainAppContextPareser>(),
                                                                              std::make_shared<JSONLogAppContextPareser>()}));
    auto app_director = std::make_shared<JSONAppDirector>(object, app_context_director,
        std::initializer_list<std::shared_ptr<JSONAppDirector::Item>>({std::make_shared<JSONTechUiAppPareser>()}));

    app_director->construct();
    auto app = app_director->result();

    return app->run();
}


