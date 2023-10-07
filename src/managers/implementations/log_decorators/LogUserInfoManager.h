#ifndef _LOGUSERINFOMANAGER_H_
#define _LOGUSERINFOMANAGER_H_

#include <memory>

#include "ILogger.h"
#include "UserInfoManager.h"

class LogUserInfoManager : public UserInfoManager
{
    public:
        LogUserInfoManager(std::shared_ptr<ILogger> logger,
                        std::shared_ptr<UserInfoManager> manager);
        virtual ~LogUserInfoManager(void) override = default;

        virtual UserMapper::Map getInfo(std::string hash) const override;
        virtual void updateInfo(std::string hash, const UserMapper::Map &map) override;
        virtual bool isHuman(std::string hash) const override;
        virtual UserMapper::Map getHuman(std::string hash) const override;

    private:
        std::shared_ptr<ILogger> logger;
        std::shared_ptr<UserInfoManager> manager;
};

DEF_EX(CommonLogUserInfoManagerException, CommonUserInfoManagerException,
       "Common LogUserInfoManager exception");
DEF_EX(NullptrLogUserInfoManagerException, CommonLogUserInfoManagerException,
       "Nullptr occured");

#endif

