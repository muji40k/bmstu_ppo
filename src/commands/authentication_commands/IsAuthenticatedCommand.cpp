#include "IsAuthenticatedCommand.h"

#include "LoginManager.h"

IsAuthenticatedCommand::IsAuthenticatedCommand(const std::string hash)
    : hash(hash)
{}

void IsAuthenticatedCommand::execute(AppContext &context)
try
{
    std::shared_ptr<LoginManager> manager = context.getLoginManager();
    this->res = manager->isAuthenticated(this->hash);
}
catch (AllocationAppContextException &)
{
    throw CALL_EX(AllocationIsAuthenticatedCommandException);
}

const bool &IsAuthenticatedCommand::result(void)
{
    return this->res;
}

