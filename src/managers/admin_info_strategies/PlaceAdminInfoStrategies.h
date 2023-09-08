#ifndef _PLACEADMININFOSTRATEGIES_H_
#define _PLACEADMININFOSTRATEGIES_H_

#include <memory>

#include "ITimeChangeableRepository.h"
#include "ICriteria.h"

#include "CreateAdminInfoStrategy.h"
#include "GetAdminInfoStrategy.h"
#include "UpdateAdminInfoStrategy.h"
#include "EraseAdminInfoStrategy.h"

#include "Place.h"
#include "PlaceResource.h"
#include "PlaceCountry.h"

#include "GenericAdminInfoStrategies.h"

#ifdef ADD_STRATEGY

ADD_STRATEGY(Place);
ADD_STRATEGY(PlaceResource);
ADD_STRATEGY(PlaceCountry);

#undef ADD_STRATEGY
#endif

#endif

