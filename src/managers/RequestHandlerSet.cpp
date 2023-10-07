#include "RequestHandlerSet.h"

#include <utility>

#include "string_common.h"

RequestHandlerSet::RequestHandlerSet(std::initializer_list<std::shared_ptr<Handler>> handlers)
{
    for (auto handler : handlers)
        this->add(handler);
}

void RequestHandlerSet::add(std::shared_ptr<Handler> handler)
{
    if (nullptr == handler)
        throw CALL_EX(NullptrRequestHandlerSetException);

    auto iter = this->handlers.find(handler->state());

    if (this->handlers.end() != iter)
        throw CALL_EX(DuplicateRequestHandlerSetException);

    this->handlers.emplace(std::pair(handler->state(), handler));
}

void RequestHandlerSet::handle(AppContext &context, const MergeRequest &request)
{
    std::string state = StringCommon::to_lower(request.state);
    auto iter = this->handlers.find(state);

    if (this->handlers.end() == iter)
        throw CALL_EX(NoHandlerRequestHandlerSetException);

    (*iter).second->handle(context, request);
}

