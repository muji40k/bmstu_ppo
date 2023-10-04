#include "SetUserInfoCommand.h"

#include "UserInfoManager.h"

SetUserInfoCommand::SetUserInfoCommand(const std::string hash,
                                       const UserMapper::Map map)
    : hash(hash), map(map)
{}

void SetUserInfoCommand::execute(AppContext &context)
try
{
    std::shared_ptr<UserInfoManager> manager = context.getUserInfoManager();
    manager->updateInfo(this->hash, this->map);
}
catch (AllocationAppContextException &)
{
    throw CALL_EX(AllocationSetUserInfoCommandException);
}
catch (NotAuthenticatedUserInfoManagerException &)
{
    throw CALL_EX(NotAuthenticatedSetUserInfoCommandException);
}
catch (NotAuthorizedUserInfoManagerException &)
{
    throw CALL_EX(NotAuthorizedSetUserInfoCommandException);
}
catch (UnexpectedKeyUserInfoManagerException &)
{
    throw CALL_EX(UnexpectedKeySetUserInfoCommandException);
}
catch (CommonReadRepositoryException &er)
{
    throw CALL_EX_MSG(RepositorySetUserInfoCommandException, er.what());
}
catch (CommonWriteRepositoryException &er)
{
    throw CALL_EX_MSG(RepositorySetUserInfoCommandException, er.what());
}

