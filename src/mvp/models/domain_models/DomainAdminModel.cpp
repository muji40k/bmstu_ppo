#include "DomainAdminModel.h"

#include "IsAdminCommand.h"
#include "GetRequestsCommand.h"
#include "SetRequestStateCommand.h"

#include "UiMergeRequestSet.h"

DomainAdminModel::DomainAdminModel(std::shared_ptr<Facade> facade)
    : facade(facade)
{
    if (nullptr == facade)
        throw CALL_EX(NullptrAdminModelException);
}

bool DomainAdminModel::isAdmin(std::string hash) const
try
{
    IsAdminCommand command (hash);
    facade->run(command);

    return command.result();
}
catch (NotAuthenticatedIsAdminCommandException &)
{
    throw CALL_EX(NotAuthenticatedAdminModelException);
}
catch (CommonIsAdminCommandException &er)
{
    throw CALL_EX_MSG(RedirectAdminModelException, er.what());
}

IAdminModel::Set DomainAdminModel::getRequests(std::string hash)
try
{
    GetRequestsCommand command (hash);
    facade->run(command);

    return IAdminModel::Set(std::make_shared<UiMergeRequestSet>(command.result()));
}
catch (NotAuthenticatedGetRequestsCommandException &)
{
    throw CALL_EX(NotAuthenticatedAdminModelException);
}
catch (NotAuthorizedGetRequestsCommandException &)
{
    throw CALL_EX(NotAuthorizedAdminModelException);
}
catch (CommonGetRequestsCommandException &er)
{
    throw CALL_EX_MSG(RedirectAdminModelException, er.what());
}

void DomainAdminModel::setRequest(std::string hash, Map map)
try
{
    MergeRequest mr = UiMergeRequestMapper::unmapRequest(map);
    SetRequestStateCommand command (hash, mr);
    facade->run(command);
}
catch (NotAuthenticatedSetRequestStateCommandException &)
{
    throw CALL_EX(NotAuthenticatedAdminModelException);
}
catch (NotAuthorizedSetRequestStateCommandException &)
{
    throw CALL_EX(NotAuthorizedAdminModelException);
}
catch (CommonSetRequestStateCommandException &er)
{
    throw CALL_EX_MSG(RedirectAdminModelException, er.what());
}

