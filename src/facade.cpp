#include "facade.h"

Facade::Facade(std::shared_ptr<AppContext> context)
    : context(context)
{
    if (nullptr == context)
        throw CALL_EX(NullptrFacadeException);
}

void Facade::run(ICommand &command)
{
    command.execute(*this->context);
}

