#ifndef _LOGUSERREQUESTMANAGER_H_
#define _LOGUSERREQUESTMANAGER_H_

#include <memory>

#include "ILogger.h"
#include "UserRequestManager.h"

class LogUserRequestManager : public UserRequestManager
{
    public:
        LogUserRequestManager(std::shared_ptr<ILogger> logger,
                        std::shared_ptr<UserRequestManager> manager);
        virtual ~LogUserRequestManager(void) override = default;

        virtual std::list<UserMapper::Map> findHuman(std::string hash, const UserMapper::Map &data) const override;
        virtual void setHuman(std::string hash, const UserMapper::Map &data) const override;

    private:
        std::shared_ptr<ILogger> logger;
        std::shared_ptr<UserRequestManager> manager;
};

DEF_EX(CommonLogUserRequestManagerException, CommonUserRequestManagerException,
       "Common LogUserRequestManager exception");
DEF_EX(NullptrLogUserRequestManagerException, CommonLogUserRequestManagerException,
       "Nullptr occured");

#endif

