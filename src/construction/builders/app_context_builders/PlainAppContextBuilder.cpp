#include "PlainAppContextBuilder.h"

#include "PlainManagerAbstractFactory.h"

#include "MD5LoginManager.h"

#include "AddressGetter.h"
#include "LanguageGetter.h"
#include "SocialGetter.h"
#include "GeneralGetter.h"
#include "LivingDatesGetter.h"

#include "ApproveHandler.h"
#include "DeclineHandler.h"

void PlainAppContextBuilder::setRepositoryContext(std::shared_ptr<RepositoryContext> context)
{
    this->context_repository = context;
}

void PlainAppContextBuilder::setRegistrationHooks(const std::list<std::shared_ptr<RegistrationHook::Item>> &hooks)
{
    this->registration_hooks = hooks;
}

void PlainAppContextBuilder::setAuthorizationHooks(const std::list<std::shared_ptr<AuthorizationHook::Item>> &hooks)
{
    this->authorization_hooks = hooks;
}

void PlainAppContextBuilder::build(void)
try
{
    if (nullptr == this->context_repository)
        throw CALL_EX(NullptrAppContextBuilderException);

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

    for (auto hook : this->registration_hooks)
        rhook->add(hook);

    std::shared_ptr<AuthorizationHook> ahook = std::make_shared<AuthorizationHook>();

    for (auto hook : this->authorization_hooks)
        ahook->add(hook);

    std::shared_ptr<AppContext> acontext = std::make_shared<AppContext>(this->context_repository);
    auto afactory = std::make_shared<PlainManagerAbstractFactory>(*acontext, MD5LoginManager::hash, umapper, rqhandler, rhook, ahook);
    acontext->setManagerAbstractFactory(afactory);

    this->context_result = acontext;
    this->ready = true;
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationAppContextBuilderException);
}

std::shared_ptr<AppContext> PlainAppContextBuilder::result(void)
{
    if (!this->ready)
        throw CALL_EX(NotReadyAppContextBuilderException);

    return this->context_result;
}

