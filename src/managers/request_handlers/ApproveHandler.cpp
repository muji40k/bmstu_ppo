#include "ApproveHandler.h"

#include "UserHuman.h"

const std::string &ApproveHandler::state(void)
{
    static const std::string state = "approved";

    return state;
}

void ApproveHandler::handle(AppContext &context, const MergeRequest &request)
{
    auto repo = context.getRepositoryContext().getUserHumanRepository();
    repo->update(UserHuman(request.user->id, request.human));
}

