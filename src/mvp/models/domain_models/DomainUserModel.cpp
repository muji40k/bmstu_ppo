#include "DomainUserModel.h"

#include "UserInfoCommand.h"
#include "SetUserInfoCommand.h"
#include "HumanInfoCommand.h"
#include "FindHumanCommand.h"
#include "SetHumanCommand.h"

DomainUserModel::DomainUserModel(std::shared_ptr<Facade> facade)
    : facade(facade)
{
    if (nullptr == facade)
        throw CALL_EX(NullptrUserModelException);
}

IUserModel::Data DomainUserModel::getInfo(std::string hash) const
try
{
    UserInfoCommand command (hash);
    facade->run(command);

    return command.result();
}
catch (NotAuthenticatedUserInfoCommandException &)
{
    throw CALL_EX(NotAuthenticatedUserModelException);
}
catch (NotAuthorizedUserInfoCommandException &)
{
    throw CALL_EX(NotAuthorizedUserModelException);
}
catch (CommonUserInfoCommandException &er)
{
    throw CALL_EX_MSG(RedirectUserModelException, er.what());
}

void DomainUserModel::setInfo(std::string hash, const Data data)
try
{
    SetUserInfoCommand command (hash, data);
    facade->run(command);
}
catch (NotAuthenticatedSetUserInfoCommandException &)
{
    throw CALL_EX(NotAuthenticatedUserModelException);
}
catch (NotAuthorizedSetUserInfoCommandException &)
{
    throw CALL_EX(NotAuthorizedUserModelException);
}
catch (CommonSetUserInfoCommandException &er)
{
    throw CALL_EX_MSG(RedirectUserModelException, er.what());
}

bool DomainUserModel::isHuman(std::string hash) const
try
{
    HumanInfoCommand command (hash);
    facade->run(command);

    return command.result().first;
}
catch (NotAuthenticatedHumanInfoCommandException &)
{
    throw CALL_EX(NotAuthenticatedUserModelException);
}
catch (NotAuthorizedHumanInfoCommandException &)
{
    throw CALL_EX(NotAuthorizedUserModelException);
}
catch (CommonHumanInfoCommandException &er)
{
    throw CALL_EX_MSG(RedirectUserModelException, er.what());
}

IUserModel::Data DomainUserModel::getHuman(std::string hash) const
try
{
    HumanInfoCommand command (hash);
    facade->run(command);

    if (command.result().first)
        return command.result().second;

    return {};
}
catch (NotAuthenticatedHumanInfoCommandException &)
{
    throw CALL_EX(NotAuthenticatedUserModelException);
}
catch (NotAuthorizedHumanInfoCommandException &)
{
    throw CALL_EX(NotAuthorizedUserModelException);
}
catch (CommonHumanInfoCommandException &er)
{
    throw CALL_EX_MSG(RedirectUserModelException, er.what());
}

std::list<IUserModel::Data> DomainUserModel::findHuman(std::string hash, const Data data)
try
{
    FindHumanCommand command (hash, data);
    facade->run(command);

    return command.result();
}
catch (NotAuthenticatedFindHumanCommandException &)
{
    throw CALL_EX(NotAuthenticatedUserModelException);
}
catch (NotAuthorizedFindHumanCommandException &)
{
    throw CALL_EX(NotAuthorizedUserModelException);
}
catch (CommonFindHumanCommandException &er)
{
    throw CALL_EX_MSG(RedirectUserModelException, er.what());
}

void DomainUserModel::setHuman(std::string hash, Data data)
try
{
    SetHumanCommand command (hash, data);
    facade->run(command);
}
catch (NotAuthenticatedSetHumanCommandException &)
{
    throw CALL_EX(NotAuthenticatedUserModelException);
}
catch (NotAuthorizedSetHumanCommandException &)
{
    throw CALL_EX(NotAuthorizedUserModelException);
}
catch (CommonSetHumanCommandException &er)
{
    throw CALL_EX_MSG(RedirectUserModelException, er.what());
}

