#include "DomainLoginModel.h"

#include "LoginCommand.h"
#include "RegisterCommand.h"
#include "UpdateCommand.h"
#include "ExitCommand.h"

DomainLoginModel::DomainLoginModel(std::shared_ptr<Facade> facade)
    : facade(facade)
{
    if (nullptr == facade)
        throw CALL_EX(NullptrLoginModelException);
}

std::string DomainLoginModel::login(std::string email, std::string password)
try
{
    LoginCommand command (email, password);
    facade->run(command);

    return command.result();
}
catch (CommonLoginCommandException &er)
{
    throw CALL_EX_MSG(RedirectLoginModelException, er.what());
}

std::string DomainLoginModel::update(std::string hash)
try
{
    UpdateCommand command (hash);
    facade->run(command);

    return command.result();
}
catch (NotAuthenticatedUpdateCommandException &)
{
    throw CALL_EX(NotAuthenticatedLoginModelException);
}
catch (CommonLoginCommandException &er)
{
    throw CALL_EX_MSG(RedirectLoginModelException, er.what());
}

void DomainLoginModel::registerUser(std::string email, std::string password, std::string name)
try
{
    RegisterCommand command (name, email, password);
    facade->run(command);
}
catch (CommonRegisterCommandException &er)
{
    throw CALL_EX_MSG(RedirectLoginModelException, er.what());
}

void DomainLoginModel::exit(std::string hash)
try
{
    ExitCommand command (hash);
    facade->run(command);
}
catch (CommonExitCommandException &er)
{
    throw CALL_EX_MSG(RedirectLoginModelException, er.what());
}

