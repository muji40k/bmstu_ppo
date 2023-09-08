#ifndef _ADMINREQUESTMANAGER_H_
#define _ADMINREQUESTMANAGER_H_

#include <memory>
#include <string>

#include "manager_exceptions.h"

#include "AppContext.h"
#include "RequestHandlerSet.h"

class RequestSetIterator
{
    public:
        RequestSetIterator(std::shared_ptr<IRepositoryIterator<MergeRequest>> iter);

        MergeRequest operator * (void) const;
        RequestSetIterator &operator ++ (int);
        bool operator != (const RequestSetIterator &iter);

    private:
        std::shared_ptr<IRepositoryIterator<MergeRequest>> iter;
};

class RequestSet
{
    public:
        RequestSet(std::shared_ptr<IRepositorySet<MergeRequest>> set);

        RequestSetIterator begin(void);
        RequestSetIterator end(void);

    private:
        std::shared_ptr<IRepositorySet<MergeRequest>> requests;
        std::shared_ptr<IRepositoryIterator<MergeRequest>> b = nullptr;
        std::shared_ptr<IRepositoryIterator<MergeRequest>> e = nullptr;
};

class AdminRequestManager
{
    public:
        AdminRequestManager(AppContext &context, RequestHandlerSet &handler);
        virtual ~AdminRequestManager(void) = default;

        virtual RequestSet getRequests(std::string hash);
        virtual void updateRequest(std::string hash, const MergeRequest &request);

    private:
        AppContext &context;
        RequestHandlerSet &handler;
};

DEF_EX(CommonRequestSetIteratorException, ManagerException,
       "Common RequestSetIterator exception");
DEF_EX(NullptrRequestSetIteratorException, CommonRequestSetIteratorException,
       "RequestSetIterator Nullptr exception");

DEF_EX(CommonRequestSetException, ManagerException,
       "Common RequestSet exception");
DEF_EX(NullptrRequestSetException, CommonRequestSetException,
       "RequestSet Nullptr exception");

DEF_EX(CommonAdminRequestManagerException, ManagerException,
       "Common UserRequestManager exception");
DEF_EX(NotAuthenticatedAdminRequestManagerException, CommonAdminRequestManagerException,
       "Hash doesn't specify any user");
DEF_EX(NotAuthorizedAdminRequestManagerException, CommonAdminRequestManagerException,
       "User isn't an admin");
DEF_EX(NotExistAdminRequestManagerException, CommonAdminRequestManagerException,
       "Specified request doesn't exist");

#endif

