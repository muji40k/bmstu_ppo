#ifndef _TECHUIUSERITEM_H_
#define _TECHUIUSERITEM_H_

#include <unordered_map>

#include "TechUi.h"
#include "IUserView.h"

class TechUiUserItem : public TechUi::Item, public IUserView
{
    public:
        TechUiUserItem(void);
        virtual ~TechUiUserItem(void) override = default;
        virtual bool check(std::string command) override;
        virtual int perform(std::string command, std::string &hash) override;
    
        virtual void onGetInfo(IUserModel::Data data) override;
        virtual void onIsHuman(bool mark) override;
        virtual void onGetHuman(IUserModel::Data data) override;
        virtual void onFindHuman(std::list<IUserModel::Data> result) override;

        virtual void onNotAuthenticated(void) override;
        virtual void onNotAuthorized(void) override;
        virtual void onError(std::string message) override;

    private:
        virtual void getInfo(std::string hash);
        virtual void setInfo(std::string hash);
        virtual void isHuman(std::string hash);
        virtual void getHuman(std::string hash);
        virtual void findHuman(std::string hash);
        virtual void setHuman(std::string hash);

    private:
        using Handler = void (TechUiUserItem::*)(std::string);

    private:
        std::unordered_map<std::string, Handler> handlers;
        std::list<IUserModel::Data> sets;
};

#endif

