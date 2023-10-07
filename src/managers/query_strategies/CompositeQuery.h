#ifndef _COMPOSITEQUERY_H_
#define _COMPOSITEQUERY_H_

#include <list>

#include "IQueryStrategy.h"

class CompositeQuery : public IQueryStrategy
{
    public:
        virtual ~CompositeQuery(void) override = default;
        virtual void execute(AppContext &context) override;

        void addQuery(IQueryStrategy &query);

    private:
        std::list<IQueryStrategy *> queries;
};

#endif

