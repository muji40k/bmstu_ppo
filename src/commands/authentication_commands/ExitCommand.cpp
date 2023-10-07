#include "ExitCommand.h"

#include "LoginManager.h"

ExitCommand::ExitCommand(const std::string hash)
    : hash(hash)
{}

void ExitCommand::execute(AppContext &context)
try
{
    std::shared_ptr<LoginManager> manager = context.getLoginManager();
    manager->exit(this->hash);
}
catch (AllocationAppContextException &)
{
    throw CALL_EX(AllocationExitCommandException);
}

