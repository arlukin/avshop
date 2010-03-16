#ifndef CHECKOUTPANEL_H
#define CHECKOUTPANEL_H

#include "Wt/WStackedWidget"
using namespace Wt;

class CheckOutPanel : public WStackedWidget
{
public:
    CheckOutPanel();

    void refresh();

    void goToCheckOutPage();
    void goToConfirmPage();
    void goToCompletedPage();
};

#endif // CHECKOUTPANEL_H
