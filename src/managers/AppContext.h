#ifndef _APPCONTEXT_H_
#define _APPCONTEXT_H_

#include <memory>
#include <vector>

#include "manager_exceptions.h"

#include "RepositoryContext.h"
#include "ManagerAbstractFactory.h"

class AppContext
{
    public:
        AppContext(std::shared_ptr<RepositoryContext> repository_context);

        void setManagerAbstractFactory(std::shared_ptr<ManagerAbstractFactory> factory);

        RepositoryContext &getRepositoryContext(void) const;

    private:
        void reset(void);

    private:
        std::shared_ptr<RepositoryContext> context;
        std::shared_ptr<ManagerAbstractFactory> factory = nullptr;
        static const std::vector<void (AppContext::*)(void)> reset_functions;

#define ADD_REPO(type)                         \
    public:                                    \
        std::shared_ptr<type> get##type(void); \
    private:                                   \
        void reset##type(void);                \
        std::shared_ptr<type> _##type = nullptr

        ADD_REPO(LoginManager);
        ADD_REPO(AuthorizationManager);
        ADD_REPO(UserInfoManager);
        ADD_REPO(AdminInfoManager);
        ADD_REPO(UserRequestManager);
        ADD_REPO(AdminRequestManager);
        ADD_REPO(QueryManager);

#undef ADD_REPO
};

DEF_EX(CommonAppContextException, ManagerException,
       "Common AppContext Exception");
DEF_EX(FactoryNullptrAppContextException, CommonAppContextException,
       "Passed factory is represented with nullptr");
DEF_EX(AllocationAppContextException, CommonAppContextException,
       "Unable to allocate manager");
DEF_EX(FactoryNotSetAppContextException, CommonAppContextException,
       "Manager factory not set");

#endif

