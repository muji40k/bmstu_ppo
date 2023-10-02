#ifndef _ICRITERIAVISITORRESULT_H_
#define _ICRITERIAVISITORRESULT_H_

#include "ICriteriaVisitor.h"

template <typename Type>
class ICriteriaVisitorResult : public ICriteriaVisitor
{
    public:
        virtual ~ICriteriaVisitorResult(void) = default;
        virtual const Type &result(void) const = 0;
};

#endif

