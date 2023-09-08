#ifndef _ICRITERIABUILDER_H_
#define _ICRITERIABUILDER_H_

#include <memory>

#include "ICriteria.h"

class ICriteriaBuilder
{
    public:
        virtual ~ICriteriaBuilder(void) = default;
        virtual std::shared_ptr<const ICriteria> get(void) const = 0;
};

#endif

