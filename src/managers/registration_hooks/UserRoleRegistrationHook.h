#ifndef _USERROLEREGISTRATIONHOOK_H_
#define _USERROLEREGISTRATIONHOOK_H_

#include "RegistrationHook.h"

class UserRoleRegistrationHook : public RegistrationHook::Item
{
    public:
        virtual ~UserRoleRegistrationHook(void) override = default;
        virtual void perform(RepositoryContext &context, const User &user) override;
};

#endif

