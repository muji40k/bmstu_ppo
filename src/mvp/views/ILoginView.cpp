#include "ILoginView.h"

void ILoginView::setPresenter(LoginPresenter *presenter)
{
    this->presenter = presenter;
}

void ILoginView::onPresenterDestroied(void)
{
    this->presenter = nullptr;
}

