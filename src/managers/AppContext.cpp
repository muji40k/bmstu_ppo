#include "AppContext.h"

AppContext::AppContext(std::shared_ptr<RepositoryContext> repository_context)
    : context(repository_context)
{
    if (nullptr == repository_context)
        throw CALL_EX(FactoryNullptrAppContextException);
}

void AppContext::setManagerAbstractFactory(std::shared_ptr<ManagerAbstractFactory> factory)
{
    if (nullptr == factory)
        throw CALL_EX(FactoryNullptrAppContextException);

    this->factory = factory;
    this->reset();
}

void AppContext::reset(void)
{
    for (auto func : AppContext::reset_functions)
        (this->*func)();
}

RepositoryContext &AppContext::getRepositoryContext(void) const
{
    return *this->context;
}

#define DEFINE_GET(type)                                      \
void AppContext::reset##type(void)                            \
{                                                             \
    this->_##type = nullptr;                                  \
}                                                             \
                                                              \
std::shared_ptr<type> AppContext::get##type(void)             \
{                                                             \
    if (nullptr == this->_##type)                             \
    {                                                         \
        if (nullptr == this->factory)                         \
            throw CALL_EX(FactoryNotSetAppContextException);  \
                                                              \
        try                                                   \
        {                                                     \
            this->_##type = this->factory->make##type();      \
        }                                                     \
        catch (AllocationManagerAbstractFactoryException &er) \
        {                                                     \
            throw CALL_EX_MSG(AllocationAppContextException,  \
                              "Unable to allocate " #type);   \
        }                                                     \
    }                                                         \
                                                              \
    return this->_##type;                                     \
}

DEFINE_GET(LoginManager)
DEFINE_GET(AuthorizationManager)
DEFINE_GET(UserInfoManager)
DEFINE_GET(AdminInfoManager)
DEFINE_GET(UserRequestManager)
DEFINE_GET(AdminRequestManager)
DEFINE_GET(QueryManager)

const std::vector<void (AppContext::*)(void)> AppContext::reset_functions =
{
    &AppContext::resetLoginManager,
    &AppContext::resetAuthorizationManager,
    &AppContext::resetUserInfoManager,
    &AppContext::resetAdminInfoManager,
    &AppContext::resetUserRequestManager,
    &AppContext::resetAdminRequestManager,
    &AppContext::resetQueryManager
};


