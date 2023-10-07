#ifndef _REQUESTHANDLERSET_H_
#define _REQUESTHANDLERSET_H_

#include <memory>
#include <initializer_list>
#include <unordered_map>
#include <string>

#include "manager_exceptions.h"

#include "AppContext.h"
#include "MergeRequest.h"

class RequestHandlerSet
{
    public:
        class Handler
        {
            public:
                virtual ~Handler(void) = default;
                virtual const std::string &state(void) = 0;
                virtual void handle(AppContext &context, const MergeRequest &request) = 0;
        };

    public:
        RequestHandlerSet(void) = default;
        RequestHandlerSet(std::initializer_list<std::shared_ptr<Handler>> handlers);

        void add(std::shared_ptr<Handler> handler);
        void handle(AppContext &context, const MergeRequest &request);

    private:
        std::unordered_map<std::string, std::shared_ptr<Handler>> handlers;
};

DEF_EX(CommonRequestHandlerSetException, ManagerException,
       "Common RequestHandlerSet exception");
DEF_EX(NullptrRequestHandlerSetException, CommonRequestHandlerSetException,
       "Nullptr occured");
DEF_EX(DuplicateRequestHandlerSetException, CommonRequestHandlerSetException,
       "Gettter duplicate");
DEF_EX(NoHandlerRequestHandlerSetException, CommonRequestHandlerSetException,
       "No handler for specified state");

#endif

