#include "UpdateCommand.h"

#include "LoginManager.h"

UpdateCommand::UpdateCommand(const std::string hash) : inhash(hash)
{}

void UpdateCommand::execute(AppContext &context)
try
{
    std::shared_ptr<LoginManager> manager = context.getLoginManager();
    this->hash = manager->update(this->inhash);
    this->ready = true;
}
catch (AllocationAppContextException &)
{
    throw CALL_EX(AllocationUpdateCommandException);
}
catch (NotAuthenticatedException &)
{
    throw CALL_EX(NotAuthenticatedUpdateCommandException);
}
catch (NoUserException &)
{
    throw CALL_EX(NoUserUpdateCommandException);
}
catch (AlreadyLoggedinException &)
{
    throw CALL_EX(AlreadyLoggedinUpdateCommandException);
}
catch (CommonReadRepositoryException &er)
{
    throw CALL_EX_MSG(RepositoryUpdateCommandException, er.what());
}

const std::string &UpdateCommand::result(void)
{
    if (!this->ready)
        throw CALL_EX(NotPerformedUpdateCommandException);

    this->ready = false;

    return this->hash;
}

