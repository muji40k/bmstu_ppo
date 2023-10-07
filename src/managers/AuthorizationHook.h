#ifndef _AUTHORIZATIONHOOK_H_
#define _AUTHORIZATIONHOOK_H_

#include <memory>
#include <list>
#include <initializer_list>

#include "manager_exceptions.h"

#include "RepositoryContext.h"
#include "User.h"

class AuthorizationHook
{
    public:
        class Item
        {
            public:
                virtual ~Item(void) = default;
                virtual bool perform(RepositoryContext &context, const User &user,
                                     const std::string &name) = 0;
        };

    public:
        AuthorizationHook(void) = default;
        AuthorizationHook(std::initializer_list<std::shared_ptr<Item>> hooks);

        void add(std::shared_ptr<Item> hook);

        template <typename Container>
        bool perform(RepositoryContext &context, const User &user,
                     const Container &roles) const;

    private:
        std::list<std::shared_ptr<Item>> hooks;
};

DEF_EX(CommonAuthorizationHookException, ManagerException,
       "Common AuthorizationHook exception");
DEF_EX(NullptrAuthorizationHookException, CommonAuthorizationHookException,
       "Nullptr occured");

#include "AuthorizationHook.hpp"

#endif

