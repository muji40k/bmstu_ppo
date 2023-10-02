#include "setupMockTest.h"

#include "MD5LoginManager.h"

#include "AddressGetter.h"
#include "LanguageGetter.h"
#include "SocialGetter.h"
#include "GeneralGetter.h"
#include "LivingDatesGetter.h"

#include "ApproveHandler.h"
#include "DeclineHandler.h"

#include "UserHumanRegistrationHook.h"

#include "PlainManagerAbstractFactory.h"
#include "RepositoryContext.h"
#include "MockRepositoryAbstractFactory.h"

std::shared_ptr<AppContext> setupRepositories(void)
{
    std::shared_ptr<RepositoryAbstractFactory> mrfactory = std::make_shared<MockRepositoryAbstractFactory>();
    std::shared_ptr<RepositoryContext> rcontext = std::make_shared<RepositoryContext>(mrfactory);
    std::shared_ptr<AppContext> acontext = std::make_shared<AppContext>(rcontext);
    std::shared_ptr<UserMapper> umapper = std::make_shared<UserMapper>();
    umapper->add(std::make_shared<AddressGetter>());
    umapper->add(std::make_shared<LanguageGetter>());
    umapper->add(std::make_shared<SocialGetter>());
    umapper->add(std::make_shared<GeneralGetter>());
    umapper->add(std::make_shared<LivingDatesGetter>());
    std::shared_ptr<RequestHandlerSet> rqhandler = std::make_shared<RequestHandlerSet>();
    rqhandler->add(std::make_shared<ApproveHandler>());
    rqhandler->add(std::make_shared<DeclineHandler>());
    std::shared_ptr<RegistrationHook> rhook = std::make_shared<RegistrationHook>();
    rhook->add(std::make_shared<UserHumanRegistrationHook>());
    std::shared_ptr<PlainManagerAbstractFactory> afactory = std::make_shared<PlainManagerAbstractFactory>(*acontext, MD5LoginManager::hash, umapper, rqhandler, rhook);
    acontext->setManagerAbstractFactory(afactory);

    return acontext;
}

