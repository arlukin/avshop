#include <sstream>

#include "Wt/WContainerWidget"
#include "Wt/WMenu"
#include "Wt/WTable"
#include "Wt/WLengthValidator"
#include "Wt/WLabel"
#include "Wt/WBreak"
#include "Wt/WText"
#include "Wt/WCheckBox"
#include "Wt/WButtonGroup"
#include "Wt/WRadioButton"

#include "AVString.h"
#include "ShopApplication.h"
#include "ForgotPasswordPanel.h"
#include "NewAccountPanel.h"
#include "Widget/UserWidget.h"

#include "CheckOutPanel/CheckOutPanel.h"
#include "CheckOutPanel/CompletedPage.h"

CompletedPage::CompletedPage()
{
    setTitle("Completed");
    setStyleClass("Wt-panel check_out_panel");

    WContainerWidget * container = new WContainerWidget();
    setCentralWidget(container);

    new Wt::WText("Your reservation has now been completed, an email with all details has been sent to you.", container);
}


