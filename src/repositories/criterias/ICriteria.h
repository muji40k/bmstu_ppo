#ifndef _ICRITERIA_H_
#define _ICRITERIA_H_

class ICriteriaVisitor;

class ICriteria
{
    public:
        virtual ~ICriteria(void) = default;
        virtual void accept(ICriteriaVisitor &visitor) const = 0;
};

#endif

