#ifndef _TECHUILOGINITEM_H_
#define _TECHUILOGINITEM_H_

#include <unordered_map>

#include "TechUi.h"
#include "ILoginView.h"

class TechUiLoginItem : public TechUi::Item, public ILoginView
{
    public:
        TechUiLoginItem(std::string &hash);
        virtual ~TechUiLoginItem(void) override = default;
        virtual bool check(std::string command) override;
        virtual int perform(std::string command, std::string &hash) override;

        virtual void onLoginSuccess(std::string hash) override;
        virtual void onLoginFailure(std::string message) override;
        virtual void onUpdateSuccess(std::string hash) override;
        virtual void onUpdateFailure(std::string message) override;
        virtual void onRegisterSuccess(void) override;
        virtual void onRegisterFailure(std::string message) override;
        virtual void onExit(void) override;
        virtual void onError(std::string message) override;

    private:
        using Handler = void (TechUiLoginItem::*)(void);

    private:
        void login(void);
        void update(void);
        void registerUser(void);
        void exit(void);

    private:
        std::string &hash;
        std::unordered_map<std::string, Handler> handlers;
};

#endif

