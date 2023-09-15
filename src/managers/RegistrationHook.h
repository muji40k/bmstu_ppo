#ifndef _REGISTRATIONHOOK_H_
#define _REGISTRATIONHOOK_H_

#include <memory>
#include <list>
#include <initializer_list>

#include "manager_exceptions.h"

#include "RepositoryContext.h"
#include "User.h"

class RegistrationHook
{
    public:
        class Item
        {
            public:
                virtual ~Item(void) = default;
                virtual void perform(RepositoryContext &context, const User &user) = 0;
        };

    public:
        RegistrationHook(void) = default;
        RegistrationHook(std::initializer_list<std::shared_ptr<Item>> hooks);

        void add(std::shared_ptr<Item> hook);
        void perform(RepositoryContext &context, const User &user) const;

    private:
        std::list<std::shared_ptr<Item>> hooks;
};

DEF_EX(CommonRegistrationHookException, ManagerException,
       "Common RegistrationHook exception");
DEF_EX(NullptrRegistrationHookException, CommonRegistrationHookException,
       "Nullptr occured");

#endif

