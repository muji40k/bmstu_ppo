#ifndef _TECHUIAPPBUILDER_H_
#define _TECHUIAPPBUILDER_H_

#include "IAppBuilder.h"

class TechUIAppBuilder : public IAppBuilder
{
    public:
        virtual ~TechUIAppBuilder(void) override = default;
        virtual void setAppContext(std::shared_ptr<AppContext> context) override;
        virtual void build(void) override;
        virtual std::shared_ptr<App> result(void) override;

    private:
        bool ready = false;
        std::shared_ptr<AppContext> context_app = nullptr;
        std::shared_ptr<App> context_result = nullptr;
};


#endif

