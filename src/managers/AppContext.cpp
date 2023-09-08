#include "AppContext.h"

AppContext::AppContext(std::shared_ptr<ManagerAbstractFactory> factory,
                       std::shared_ptr<RepositoryContext> repository_context)
    : factory(factory), context(repository_context)
{
    if (nullptr == factory || nullptr == repository_context)
        throw CALL_EX(FactoryNullptrAppContextException);
}

RepositoryContext &AppContext::getRepositoryContext(void) const
{
    return *this->context;
}

#define DEFINE_GET(type)                                      \
std::shared_ptr<type> AppContext::get##type(void)             \
{                                                             \
    if (nullptr == this->_##type)                             \
    {                                                         \
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

