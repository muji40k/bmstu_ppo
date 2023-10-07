#include "IAdminView.h"

void IAdminView::setPresenter(AdminPresenter *presenter)
{
    this->presenter = presenter;
}

void IAdminView::onPresenterDestroied(void)
{
    this->presenter = nullptr;
}

