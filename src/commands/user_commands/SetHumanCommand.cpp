#include "SetHumanCommand.h"

#include "UserRequestManager.h"

SetHumanCommand::SetHumanCommand(const std::string hash, const UserMapper::Map map)
    : hash(hash), in_map(map)
{}

void SetHumanCommand::execute(AppContext &context)
try
{
    std::shared_ptr<UserRequestManager> manager = context.getUserRequestManager();
    manager->setHuman(this->hash, this->in_map);
}
catch (AllocationAppContextException &)
{
    throw CALL_EX(AllocationSetHumanCommandException);
}
catch (AllocationRepositoryContextException &)
{
    throw CALL_EX(AllocationSetHumanCommandException);
}
catch (NotAuthenticatedUserRequestManagerException &)
{
    throw CALL_EX(NotAuthenticatedSetHumanCommandException);
}
catch (UnsuitableDataUserRequestManagerException &er)
{
    throw CALL_EX_MSG(WrongDataSetHumanCommandException, er.what());
}
catch (NotFoundUserRequestManagerException &)
{
    throw CALL_EX(NotFoundSetHumanCommandException);
}
catch (CommonReadRepositoryException &er)
{
    throw CALL_EX_MSG(RepositorySetHumanCommandException, er.what());
}
catch (CommonWriteRepositoryException &er)
{
    throw CALL_EX_MSG(RepositorySetHumanCommandException, er.what());
}
catch (CommonTimeChangeableRepositoryException &er)
{
    throw CALL_EX_MSG(RepositorySetHumanCommandException, er.what());
}

