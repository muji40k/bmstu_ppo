#include "UserRoleRegistrationHook.h"

#include "UserRole.h"

void UserRoleRegistrationHook::perform(RepositoryContext &context, const User &user)
{
    auto repo = context.getUserRoleRepository();
    UserRole role;
    role.userId = user.id;
    role.role = "plainuser";
    repo->create(role);
}

