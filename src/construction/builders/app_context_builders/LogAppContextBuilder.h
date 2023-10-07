#ifndef _LOGAPPCONTEXTBUILDER_H_
#define _LOGAPPCONTEXTBUILDER_H_

#include "IAppContextBuilder.h"

#include "ILogger.h"

class LogAppContextBuilder : public IAppContextBuilder
{
    public:
        class LoggerCreator
        {
            public:
                virtual ~LoggerCreator(void) = default;
                virtual std::shared_ptr<ILogger> create(void) = 0;
        };

    public:
        virtual ~LogAppContextBuilder(void) = default;
        virtual void setRepositoryContext(std::shared_ptr<RepositoryContext> context) override;
        virtual void setRegistrationHooks(const std::list<std::shared_ptr<RegistrationHook::Item>> &hooks) override;
        virtual void setAuthorizationHooks(const std::list<std::shared_ptr<AuthorizationHook::Item>> &hooks) override;
        virtual void build(void) override;
        virtual std::shared_ptr<AppContext> result(void) override;

        void setLoggerCreator(std::shared_ptr<LoggerCreator> creator);

    private:
        bool ready = false;
        std::shared_ptr<LoggerCreator> creator = nullptr;
        std::shared_ptr<RepositoryContext> context_repository = nullptr;
        std::shared_ptr<AppContext> context_result = nullptr;
        std::list<std::shared_ptr<RegistrationHook::Item>> registration_hooks;
        std::list<std::shared_ptr<AuthorizationHook::Item>> authorization_hooks;
};

#endif

