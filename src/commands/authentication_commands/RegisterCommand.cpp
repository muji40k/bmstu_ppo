#include "RegisterCommand.h"

#include "LoginManager.h"

RegisterCommand::RegisterCommand(const std::string name, const std::string email,
                                 const std::string password)
    : user(User(0, name, password, email))
{}

void RegisterCommand::execute(AppContext &context)
try
{
    std::shared_ptr<LoginManager> manager = context.getLoginManager();
    manager->registerUser(this->user);
}
catch (AllocationAppContextException &)
{
    throw CALL_EX(AllocationRegisterCommandException);
}
catch (AlreadyRegisteredException &)
{
    throw CALL_EX(AlreadyRegisteredCommandException);
}
catch (CommonReadRepositoryException &er)
{
    throw CALL_EX_MSG(RepositoryRegisterCommandException, er.what());
}
catch (CommonWriteRepositoryException &er)
{
    throw CALL_EX_MSG(RepositoryRegisterCommandException, er.what());
}

