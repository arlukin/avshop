#include <sstream>

#include "CheckOutPanel/ConfirmPage.h"
#include "CheckOutPanel/CheckOutPage.h"
#include "CheckOutPanel/CompletedPage.h"

#include "CheckOutPanel/CheckOutPanel.h"

CheckOutPanel::CheckOutPanel()
{
    addWidget(new CheckOutPage());
    addWidget(new ConfirmPage());
    addWidget(new CompletedPage());
}

void CheckOutPanel::refresh()
{
    goToCheckOutPage();
}

void CheckOutPanel::goToCheckOutPage()
{
    setCurrentIndex(0);
    widget(0)->refresh();
}

void CheckOutPanel::goToConfirmPage()
{
    setCurrentIndex(1);
    widget(1)->refresh();
}

void CheckOutPanel::goToCompletedPage()
{
    setCurrentIndex(2);
    widget(2)->refresh();
}
