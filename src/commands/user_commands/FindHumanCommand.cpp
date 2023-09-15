#include "FindHumanCommand.h"

#include "UserRequestManager.h"

FindHumanCommand::FindHumanCommand(const std::string hash, const UserMapper::Map map)
    : hash(hash), in_map(map)
{}

void FindHumanCommand::execute(AppContext &context)
try
{
    std::shared_ptr<UserRequestManager> manager = context.getUserRequestManager();
    this->out = manager->findHuman(this->hash, this->in_map);
}
catch (AllocationAppContextException &)
{
    throw CALL_EX(AllocationFindHumanCommandException);
}
catch (AllocationRepositoryContextException &)
{
    throw CALL_EX(AllocationFindHumanCommandException);
}
catch (NotAuthenticatedUserRequestManagerException &)
{
    throw CALL_EX(NotAuthenticatedFindHumanCommandException);
}
catch (UnspecifiedDataUserRequestManagerException &er)
{
    throw CALL_EX_MSG(WrongDataFindHumanCommandException, er.what());
}
catch (EmptyDataUserRequestManagerException &er)
{
    throw CALL_EX_MSG(WrongDataFindHumanCommandException, er.what());
}
catch (CommonReadRepositoryException &er)
{
    throw CALL_EX_MSG(RepositoryFindHumanCommandException, er.what());
}
catch (CommonWriteRepositoryException &er)
{
    throw CALL_EX_MSG(RepositoryFindHumanCommandException, er.what());
}
catch (CommonTimeChangeableRepositoryException &er)
{
    throw CALL_EX_MSG(RepositoryFindHumanCommandException, er.what());
}

const std::list<UserMapper::Map> &FindHumanCommand::result(void)
{
    return this->out;
}

