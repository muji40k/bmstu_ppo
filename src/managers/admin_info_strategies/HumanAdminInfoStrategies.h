#ifndef _HUMANADMININFOSTRATEGIES_H_
#define _HUMANADMININFOSTRATEGIES_H_

#include <memory>

#include "ITimeChangeableRepository.h"
#include "ICriteria.h"

#include "CreateAdminInfoStrategy.h"
#include "GetAdminInfoStrategy.h"
#include "UpdateAdminInfoStrategy.h"
#include "EraseAdminInfoStrategy.h"

#include "Human.h"
#include "HumanAddress.h"
#include "HumanLivingDates.h"
#include "HumanSocial.h"
#include "HumanGeneral.h"
#include "HumanLanguage.h"

#include "GenericAdminInfoStrategies.h"

#ifdef ADD_STRATEGY

ADD_STRATEGY(Human);
ADD_STRATEGY(HumanAddress);
ADD_STRATEGY(HumanLivingDates);
ADD_STRATEGY(HumanSocial);
ADD_STRATEGY(HumanGeneral);
ADD_STRATEGY(HumanLanguage);

#undef ADD_STRATEGY
#endif

#endif

