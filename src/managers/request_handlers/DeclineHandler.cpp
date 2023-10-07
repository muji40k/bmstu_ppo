#include "DeclineHandler.h"

#include "UserHuman.h"

const std::string &DeclineHandler::state(void)
{
    static const std::string state = "declined";

    return state;
}

void DeclineHandler::handle(AppContext &, const MergeRequest &)
{}

