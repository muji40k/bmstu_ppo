#include "UserAdminInfoStrategies.h"

UserCreateAdminInfoStrategy::UserCreateAdminInfoStrategy(const User &user)
    : user(user)
{}

void UserCreateAdminInfoStrategy::apply(AppContext &context)
{
    auto repo = context.getRepositoryContext().getUserRepository();
    repo->create(this->user);
}

UserGetAdminInfoStrategy::UserGetAdminInfoStrategy(const ICriteria &criteria)
    : criteria(&criteria)
{}

void UserGetAdminInfoStrategy::apply(AppContext &context)
{
    auto repo = context.getRepositoryContext().getUserRepository();

    if (this->criteria)
        this->res = repo->get(*this->criteria);
    else
        this->res = repo->getAll();
}

std::shared_ptr<IRepositorySet<User>> UserGetAdminInfoStrategy::result(void)
{
    return this->res;
}

UserUpdateAdminInfoStrategy::UserUpdateAdminInfoStrategy(const User &user)
    : user(user)
{}

void UserUpdateAdminInfoStrategy::apply(AppContext &context)
{
    auto repo = context.getRepositoryContext().getUserRepository();
    repo->update(this->user);
}

UserEraseAdminInfoStrategy::UserEraseAdminInfoStrategy(const ICriteria &criteria)
    : criteria(criteria)
{}

void UserEraseAdminInfoStrategy::apply(AppContext &context)
{
    auto repo = context.getRepositoryContext().getUserRepository();
    repo->erase(this->criteria);
}

UserEraseSingleAdminInfoStrategy::UserEraseSingleAdminInfoStrategy(const User &user)
    : user(user)
{}

void UserEraseSingleAdminInfoStrategy::apply(AppContext &context)
{
    auto repo = context.getRepositoryContext().getUserRepository();
    repo->erase(this->user);
}

