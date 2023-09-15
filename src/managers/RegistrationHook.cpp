#include "RegistrationHook.h"

RegistrationHook::RegistrationHook(std::initializer_list<std::shared_ptr<Item>> hooks)
{
    for (auto hook : hooks)
        this->add(hook);
}

void RegistrationHook::add(std::shared_ptr<Item> hook)
{
    if (nullptr == hook)
        throw CALL_EX(NullptrRegistrationHookException);

    this->hooks.push_back(hook);
}

void RegistrationHook::perform(RepositoryContext &context, const User &user) const
{
    for (auto hook : this->hooks)
        hook->perform(context, user);
}

