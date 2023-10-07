#ifndef _TECHUIADMINITEM_H_
#define _TECHUIADMINITEM_H_

#include <unordered_map>

#include "TechUi.h"
#include "IAdminView.h"

class TechUiAdminItem : public TechUi::Item, public IAdminView
{
    public:
        TechUiAdminItem(void);
        virtual ~TechUiAdminItem(void) override = default;
        virtual bool check(std::string command) override;
        virtual int perform(std::string command, std::string &hash) override;

        virtual void onIsAdmin(bool result) override;
        virtual void onGetRequests(IAdminModel::Set result) override;
        virtual void onGet(std::string name, IAdminModel::Set result) override;

        virtual void onNotAuthenticated(void) override;
        virtual void onNotAuthorized(void) override;
        virtual void onError(std::string message) override;

    private:
        void isAdmin(std::string hash);
        void getRequests(std::string hash);
        void setRequest(std::string hash);
        void create(std::string hash);
        void update(std::string hash);
        void remove(std::string hash);
        void get(std::string hash);

    private:
        using Handler = void (TechUiAdminItem::*)(std::string);

    private:
        std::unordered_map<std::string, Handler> handlers;
        std::unordered_map<std::string, IAdminModel::Set> sets;
};

#endif

