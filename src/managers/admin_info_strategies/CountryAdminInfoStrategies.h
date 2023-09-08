#ifndef _COUNTRYADMININFOSTRATEGIES_H_
#define _COUNTRYADMININFOSTRATEGIES_H_

#include <memory>

#include "ITimeChangeableRepository.h"
#include "ICriteria.h"

#include "CreateAdminInfoStrategy.h"
#include "GetAdminInfoStrategy.h"
#include "UpdateAdminInfoStrategy.h"
#include "EraseAdminInfoStrategy.h"

#include "Country.h"

#include "GenericAdminInfoStrategies.h"

#ifdef ADD_STRATEGY

ADD_STRATEGY(Country);

#undef ADD_STRATEGY
#endif

#endif

