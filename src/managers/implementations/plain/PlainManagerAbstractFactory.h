#ifndef _PLAINMANAGERABSTRACTFACTORY_H_
#define _PLAINMANAGERABSTRACTFACTORY_H_

#include "ManagerAbstractFactory.h"

#include "AppContext.h"
#include "UserMapper.h"
#include "RequestHandlerSet.h"
#include "LoginManager.h"
#include "RegistrationHook.h"
#include "AuthorizationHook.h"

class PlainManagerAbstractFactory : public ManagerAbstractFactory
{
    public:
        PlainManagerAbstractFactory(AppContext &context,
                                    LoginManager::HashFunc hash,
                                    std::shared_ptr<UserMapper> user_mapper,
                                    std::shared_ptr<RequestHandlerSet> handler_set,
                                    std::shared_ptr<RegistrationHook> registration_hook = nullptr,
                                    std::shared_ptr<AuthorizationHook> authorization_hook = nullptr);
        virtual ~PlainManagerAbstractFactory(void) override = default;

    private:
        AppContext &context;
        LoginManager::HashFunc hash;
        std::shared_ptr<UserMapper> user_mapper;
        std::shared_ptr<RequestHandlerSet> handler_set;
        std::shared_ptr<RegistrationHook> registration_hook;
        std::shared_ptr<AuthorizationHook> authorization_hook;

#define ADD_REPO(type) \
        virtual std::shared_ptr<type> make##type(void) override

    public:
        ADD_REPO(LoginManager);
        ADD_REPO(AuthorizationManager);
        ADD_REPO(UserInfoManager);
        ADD_REPO(AdminInfoManager);
        ADD_REPO(UserRequestManager);
        ADD_REPO(AdminRequestManager);
        ADD_REPO(QueryManager);

#undef ADD_REPO
};

DEF_EX(CommonPlainManagerAbstractFactoryException, CommonManagerAbstractFactoryException,
       "Common PlainManagerAbstractFactory exception");
DEF_EX(NullptrPlainManagerAbstractFactoryException, CommonPlainManagerAbstractFactoryException,
       "Nullptr PlainManagerAbstractFactory exception");

#endif

