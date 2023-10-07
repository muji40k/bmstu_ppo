#ifndef _PLAINAUTHORIZATIONMANAGER_H_
#define _PLAINAUTHORIZATIONMANAGER_H_

#include "AuthorizationManager.h"

class PlainAuthorizationManager : public AuthorizationManager
{
    public:
        PlainAuthorizationManager(AppContext &context,
                             std::shared_ptr<AuthorizationHook> hook = nullptr);
        virtual ~PlainAuthorizationManager(void) override = default;

        virtual bool authorize(const std::string &hash,
                               std::initializer_list<std::string> roles) override;
        virtual bool authorize(const std::string &hash,
                               std::list<std::string> roles) override;

    private:
        template <typename Container>
        bool innerAuthorize(const std::string &hash,
                            const Container &container);

        AppContext &context;
        std::shared_ptr<AuthorizationHook> hook = nullptr;
};

#endif

