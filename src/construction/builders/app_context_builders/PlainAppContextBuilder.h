#ifndef _PLAINAPPCONTEXTBUILDER_H_
#define _PLAINAPPCONTEXTBUILDER_H_

#include "IAppContextBuilder.h"

class PlainAppContextBuilder : public IAppContextBuilder
{
    public:
        virtual ~PlainAppContextBuilder(void) = default;
        virtual void setRepositoryContext(std::shared_ptr<RepositoryContext> context) override;
        virtual void setRegistrationHooks(const std::list<std::shared_ptr<RegistrationHook::Item>> &hooks) override;
        virtual void setAuthorizationHooks(const std::list<std::shared_ptr<AuthorizationHook::Item>> &hooks) override;
        virtual void build(void) override;
        virtual std::shared_ptr<AppContext> result(void) override;

    private:
        bool ready = false;
        std::shared_ptr<RepositoryContext> context_repository = nullptr;
        std::shared_ptr<AppContext> context_result = nullptr;
        std::list<std::shared_ptr<RegistrationHook::Item>> registration_hooks;
        std::list<std::shared_ptr<AuthorizationHook::Item>> authorization_hooks;
};

#endif

