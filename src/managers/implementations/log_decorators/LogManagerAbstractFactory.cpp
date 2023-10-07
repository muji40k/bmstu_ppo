#include "LogManagerAbstractFactory.h"

#include "LogLoginManager.h"
#include "LogAuthorizationManager.h"
#include "LogUserInfoManager.h"
#include "LogAdminInfoManager.h"
#include "LogUserRequestManager.h"
#include "LogAdminRequestManager.h"
#include "LogQueryManager.h"

LogManagerAbstractFactory::LogManagerAbstractFactory(std::shared_ptr<ILogger> logger,
                                  std::shared_ptr<ManagerAbstractFactory> factory)
    : logger(logger), factory(factory)
{
    if (nullptr == logger || nullptr == factory)
        throw CALL_EX(NullptrLogManagerAbstractFactoryException);
}

#define ADD_REPO(type)                                               \
std::shared_ptr<type> LogManagerAbstractFactory::make##type(void)    \
try                                                                  \
{                                                                    \
    return std::make_shared<Log##type>(this->logger,                 \
                                       this->factory->make##type()); \
}                                                                    \
catch (std::bad_alloc &)                                             \
{                                                                    \
    throw CALL_EX(AllocationManagerAbstractFactoryException);        \
}

ADD_REPO(LoginManager)
ADD_REPO(AuthorizationManager)
ADD_REPO(UserInfoManager)
ADD_REPO(AdminInfoManager)
ADD_REPO(UserRequestManager)
ADD_REPO(AdminRequestManager)
ADD_REPO(QueryManager)

