#include "Wt/WLengthValidator"
#include "Wt/WLabel"
#include "Wt/WContainerWidget"
#include "Wt/WBreak"
#include "Wt/WText"

#include "Widget/UserWidget.h"
#include "NewAccountPanel.h"

NewAccountPanel::NewAccountPanel()
{    
    UserWidget * userWidget = new UserWidget();
    setCentralWidget(userWidget);
    setTitle("Register new account");
    setStyleClass("Wt-panel new_account_panel");

    new Wt::WText("<hr />", userWidget);

    WPushButton * _okButton = new Wt::WPushButton(WString::tr("button.ok"), userWidget);
}
