#include "PlainManagerAbstractFactory.h"

#include "LoginManager.h"
#include "AuthorizationManager.h"
#include "UserInfoManager.h"
#include "AdminInfoManager.h"
#include "UserRequestManager.h"
#include "AdminRequestManager.h"
#include "QueryManager.h"

PlainManagerAbstractFactory::PlainManagerAbstractFactory(AppContext &context,
                                                         LoginManager::HashFunc hash,
                                                         std::shared_ptr<UserMapper> user_mapper,
                                                         std::shared_ptr<RequestHandlerSet> handler_set,
                                                         std::shared_ptr<RegistrationHook> registration_hook,
                                                         std::shared_ptr<AuthorizationHook> authorization_hook)
    : context(context), hash(hash), user_mapper(user_mapper), handler_set(handler_set),
      registration_hook(registration_hook), authorization_hook(authorization_hook)
{
    if (nullptr == user_mapper)
        throw CALL_EX(NullptrPlainManagerAbstractFactoryException);

    if (nullptr == hash)
        throw CALL_EX(NullptrPlainManagerAbstractFactoryException);

    if (nullptr == handler_set)
        throw CALL_EX(NullptrPlainManagerAbstractFactoryException);
}

std::shared_ptr<LoginManager> PlainManagerAbstractFactory::makeLoginManager(void)
try
{
    return std::make_shared<LoginManager>(this->context.getRepositoryContext(), this->hash, this->registration_hook);
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationManagerAbstractFactoryException);
}

std::shared_ptr<AuthorizationManager> PlainManagerAbstractFactory::makeAuthorizationManager(void)
try
{
    return std::make_shared<AuthorizationManager>(this->context, this->authorization_hook);
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationManagerAbstractFactoryException);
}

std::shared_ptr<UserInfoManager> PlainManagerAbstractFactory::makeUserInfoManager(void)
try
{
    return std::make_shared<UserInfoManager>(this->context, *this->user_mapper);
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationManagerAbstractFactoryException);
}

std::shared_ptr<AdminInfoManager> PlainManagerAbstractFactory::makeAdminInfoManager(void)
try
{
    return std::make_shared<AdminInfoManager>(this->context);
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationManagerAbstractFactoryException);
}

std::shared_ptr<UserRequestManager> PlainManagerAbstractFactory::makeUserRequestManager(void)
try
{
    return std::make_shared<UserRequestManager>(this->context, *this->user_mapper);
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationManagerAbstractFactoryException);
}

std::shared_ptr<AdminRequestManager> PlainManagerAbstractFactory::makeAdminRequestManager(void)
try
{
    return std::make_shared<AdminRequestManager>(this->context, *this->handler_set);
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationManagerAbstractFactoryException);
}

std::shared_ptr<QueryManager> PlainManagerAbstractFactory::makeQueryManager(void)
try
{
    return std::make_shared<QueryManager>(this->context);
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationManagerAbstractFactoryException);
}


