#ifndef _AUTHORIZATIONHOOK_HPP_
#define _AUTHORIZATIONHOOK_HPP_

#include "AuthorizationHook.h"

template <typename Container>
bool AuthorizationHook::perform(RepositoryContext &context, const User &user,
                                const Container &roles) const
{
    bool mark = false;

    for (auto role_iter = roles.begin();
         !mark && roles.end() != role_iter;
         ++role_iter)
        for (auto hook_iter = this->hooks.begin();
             !mark && this->hooks.end() != hook_iter;
             ++hook_iter)
            mark = (*hook_iter)->perform(context, user, *role_iter);

    return mark;
}


#endif

