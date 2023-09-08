#ifndef _IMERGEREQUESTREPOSITORY_H_
#define _IMERGEREQUESTREPOSITORY_H_

#include "IWriteRepository.h"
#include "IReadRepository.h"
#include "MergeRequest.h"

class IMergeRequestRepository : public IWriteRepository<MergeRequest>, public IReadRepository<MergeRequest>
{
    public:
        virtual ~IMergeRequestRepository(void) override = default;
};

#endif

