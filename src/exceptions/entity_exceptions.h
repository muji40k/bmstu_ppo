#ifndef _ENTITY_EXCEPTIONS_H_
#define _ENTITY_EXCEPTIONS_H_

#include "base_exception.h"

DEF_EX(EntityException, BaseException, "Common Entity exception");

DEF_EX(DateOverflowException, EntityException, "Date exided max value of 9999-12-31 23:59:59");
DEF_EX(ChronologicalException, EntityException, "Embeded entity violates container's validFrom date");

#endif

