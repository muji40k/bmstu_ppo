#include "IUserView.h"

void IUserView::setPresenter(UserPresenter *presenter)
{
    this->presenter = presenter;
}

void IUserView::onPresenterDestroied(void)
{
    this->presenter = nullptr;
}

