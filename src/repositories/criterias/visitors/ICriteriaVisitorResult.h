#ifndef _ICRITERIAVISITORRESULT_H_
#define _ICRITERIAVISITORRESULT_H_

template <typename Type>
class ICriteriaVisitorResult
{
    public:
        virtual ~ICriteriaVisitorResult(void) = default;
        virtual const Type &result(void) const = 0;
};

#endif

