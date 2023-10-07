#include "TechUIAppBuilder.h"

#include "facade.h"

#include "TechUi.h"
#include "DomainAdminModel.h"
#include "DomainUserModel.h"
#include "DomainLoginModel.h"

#include "UiCountryMapper.h"
#include "UiHumanAddressMapper.h"
#include "UiHumanGeneralMapper.h"
#include "UiHumanLanguageMapper.h"
#include "UiHumanLivingDatesMapper.h"
#include "UiHumanMapper.h"
#include "UiHumanSocialMapper.h"
#include "UiMergeRequestSet.h"
#include "UiPlaceCountryMapper.h"
#include "UiPlaceMapper.h"
#include "UiPlaceResourceMapper.h"
#include "UiUserMapper.h"

void TechUIAppBuilder::setAppContext(std::shared_ptr<AppContext> context)
{
    this->context_app = context;
}

void TechUIAppBuilder::build(void)
try
{
    if (nullptr == context_app)
        throw CALL_EX(NullptrAppBuilderException);

    auto facade = std::make_shared<Facade>(this->context_app);
    auto amodel = std::make_shared<DomainAdminModel>(facade);
    auto umodel = std::make_shared<DomainUserModel>(facade);
    auto lmodel = std::make_shared<DomainLoginModel>(facade);
    amodel->add("Human", std::make_shared<UiHumanMapper>(facade));
    amodel->add("HumanAddress", std::make_shared<UiHumanAddressMapper>(facade));
    amodel->add("HumanLivingDates", std::make_shared<UiHumanLivingDatesMapper>(facade));
    amodel->add("HumanSocial", std::make_shared<UiHumanSocialMapper>(facade));
    amodel->add("HumanGeneral", std::make_shared<UiHumanGeneralMapper>(facade));
    amodel->add("HumanLanguage", std::make_shared<UiHumanLanguageMapper>(facade));
    amodel->add("Place", std::make_shared<UiPlaceMapper>(facade));
    amodel->add("PlaceResource", std::make_shared<UiPlaceResourceMapper>(facade));
    amodel->add("PlaceCountry", std::make_shared<UiPlaceCountryMapper>(facade));
    amodel->add("Country", std::make_shared<UiCountryMapper>(facade));
    amodel->add("User", std::make_shared<UiUserMapper>(facade));

    this->context_result = std::make_shared<TechUi>(amodel, umodel, lmodel);
    this->ready = true;
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationAppBuilderException);
}

std::shared_ptr<App> TechUIAppBuilder::result(void)
{
    if (!this->ready)
        throw CALL_EX(NotReadyAppBuilderException);

    return this->context_result;
}



