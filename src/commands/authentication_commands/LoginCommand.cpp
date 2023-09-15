#include "LoginCommand.h"

#include "LoginManager.h"

LoginCommand::LoginCommand(const std::string email, const std::string password)
    : email(email), password(password)
{}

void LoginCommand::execute(AppContext &context)
try
{
    std::shared_ptr<LoginManager> manager = context.getLoginManager();
    this->hash = manager->login(this->email, this->password);
    this->ready = true;
}
catch (AllocationAppContextException &)
{
    throw CALL_EX(AllocationLoginCommandException);
}
catch (WrongLoginException &)
{
    throw CALL_EX(WrongLoginCommandException);
}
catch (AlreadyLoggedinException &)
{
    throw CALL_EX(AlreadyLoggedinCommandException);
}
catch (CommonReadRepositoryException &er)
{
    throw CALL_EX_MSG(RepositoryLoginCommandException, er.what());
}

const std::string &LoginCommand::result(void)
{
    if (!this->ready)
        throw CALL_EX(NotPerformedLoginCommandException);

    this->ready = false;

    return this->hash;
}

