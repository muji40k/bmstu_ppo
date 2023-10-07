#include "UserHumanRegistrationHook.h"

#include "UserHuman.h"

void UserHumanRegistrationHook::perform(RepositoryContext &context, const User &user)
{
    auto repo = context.getUserHumanRepository();
    repo->create(UserHuman(user.id));
}

