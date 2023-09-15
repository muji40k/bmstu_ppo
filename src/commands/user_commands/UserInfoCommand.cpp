#include "UserInfoCommand.h"

#include "UserInfoManager.h"

UserInfoCommand::UserInfoCommand(const std::string hash)
    : hash(hash)
{}

void UserInfoCommand::execute(AppContext &context)
try
{
    std::shared_ptr<UserInfoManager> manager = context.getUserInfoManager();
    this->map = manager->getInfo(this->hash);
}
catch (AllocationAppContextException &)
{
    throw CALL_EX(AllocationUserInfoCommandException);
}
catch (NotAuthenticatedUserInfoManagerException &)
{
    throw CALL_EX(NotAuthenticatedUserInfoCommandException);
}
catch (CommonReadRepositoryException &er)
{
    throw CALL_EX_MSG(RepositoryUserInfoCommandException, er.what());
}

const UserMapper::Map &UserInfoCommand::result(void)
{
    return this->map;
}

