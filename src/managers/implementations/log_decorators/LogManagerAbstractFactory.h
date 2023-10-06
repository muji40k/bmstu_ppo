#ifndef _LOGMANAGERABSTRACTFACTORY_H_
#define _LOGMANAGERABSTRACTFACTORY_H_

#include <memory>

#include "ILogger.h"
#include "ManagerAbstractFactory.h"

class LogManagerAbstractFactory : public ManagerAbstractFactory
{
    public:
        LogManagerAbstractFactory(std::shared_ptr<ILogger> logger,
                                  std::shared_ptr<ManagerAbstractFactory> factory);
        virtual ~LogManagerAbstractFactory(void) override = default;

    private:
        std::shared_ptr<ILogger> logger;
        std::shared_ptr<ManagerAbstractFactory> factory;

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

DEF_EX(CommonLogManagerAbstractFactoryException, CommonManagerAbstractFactoryException,
       "Common LogManagerAbstractFactory exception");
DEF_EX(NullptrLogManagerAbstractFactoryException, CommonLogManagerAbstractFactoryException,
       "Nullptr LogManagerAbstractFactory exception");

#endif

