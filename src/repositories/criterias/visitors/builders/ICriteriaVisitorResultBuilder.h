#ifndef _ICRITERIAVISITORRESULTBUILDER_H_
#define _ICRITERIAVISITORRESULTBUILDER_H_

#include <memory>
#include "ICriteriaVisitorResult.h"

template <typename Type>
class ICriteriaVisitorResultBuilder
{
    public:
        virtual ~ICriteriaVisitorResultBuilder(void) = default;
        virtual std::shared_ptr<ICriteriaVisitorResult<Type>> get(void) const = 0;
};

DEF_EX(CommonCriteriaVisitorResultBuilderException, RepositoryException,
       "Common CriteriaVisitorResultBuilder Exception");

#endif

