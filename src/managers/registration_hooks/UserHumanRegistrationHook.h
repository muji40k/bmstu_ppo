#ifndef _USERHUMANREGISTRATIONHOOK_H_
#define _USERHUMANREGISTRATIONHOOK_H_

#include "RegistrationHook.h"

class UserHumanRegistrationHook : public RegistrationHook::Item
{
    public:
        virtual ~UserHumanRegistrationHook(void) override = default;
        virtual void perform(RepositoryContext &context, const User &user) override;
};

#endif

