#include "HumanInfoCommand.h"

#include "UserInfoManager.h"

HumanInfoCommand::HumanInfoCommand(const std::string hash)
    : hash(hash)
{}

void HumanInfoCommand::execute(AppContext &context)
try
{
    std::shared_ptr<UserInfoManager> manager = context.getUserInfoManager();
    this->out.first = false;
    this->out.second.clear();

    if (!manager->isHuman(this->hash))
        return;

    this->out.first = true;
    this->out.second = manager->getHuman(this->hash);
}
catch (AllocationAppContextException &)
{
    throw CALL_EX(AllocationHumanInfoCommandException);
}
catch (AllocationRepositoryContextException &)
{
    throw CALL_EX(AllocationHumanInfoCommandException);
}
catch (NotAuthenticatedUserInfoManagerException &)
{
    throw CALL_EX(NotAuthenticatedHumanInfoCommandException);
}
catch (CommonReadRepositoryException &er)
{
    throw CALL_EX_MSG(RepositoryHumanInfoCommandException, er.what());
}
catch (CommonWriteRepositoryException &er)
{
    throw CALL_EX_MSG(RepositoryHumanInfoCommandException, er.what());
}
catch (CommonTimeChangeableRepositoryException &er)
{
    throw CALL_EX_MSG(RepositoryHumanInfoCommandException, er.what());
}

const std::pair<bool, UserMapper::Map> &HumanInfoCommand::result(void)
{
    return this->out;
}

