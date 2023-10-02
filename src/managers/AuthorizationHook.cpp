#include "AuthorizationHook.h"

AuthorizationHook::AuthorizationHook(std::initializer_list<std::shared_ptr<Item>> hooks)
{
    for (auto hook : hooks)
        this->add(hook);
}

void AuthorizationHook::add(std::shared_ptr<Item> hook)
{
    if (nullptr == hook)
        throw CALL_EX(NullptrAuthorizationHookException);

    this->hooks.push_back(hook);
}

