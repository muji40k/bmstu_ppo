#ifndef _ICRITERIAVISITORBUILDER_H_
#define _ICRITERIAVISITORBUILDER_H_

#include <memory>
#include "ICriteriaVisitor.h"

class ICriteriaVisitorBuilder
{
    public:
        virtual ~ICriteriaVisitorBuilder(void) = default;
        virtual std::shared_ptr<ICriteriaVisitor> get(void) const = 0;
};

#endif

