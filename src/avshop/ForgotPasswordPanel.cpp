#include "Wt/WLengthValidator"
#include "Wt/WLabel"
#include "Wt/WContainerWidget"
#include "Wt/WBreak"
#include "Wt/WText"

#include "ForgotPasswordPanel.h"

ForgotPasswordPanel::ForgotPasswordPanel()
{
    _container = new WContainerWidget();
    setCentralWidget(_container);
    setTitle("Forgot password");
    setStyleClass("Wt-panel forgot_password_panel");

    //
    _table = new Wt::WTable(_container);

    // Email
    createLineEdit("Email:");

    WLineEdit * password = createLineEdit("Password:");
    password->setEchoMode(WLineEdit::Password);

    new Wt::WText("<hr />", _container);

    _okButton = new Wt::WPushButton(WString::tr("button.ok"), _container);
}

WLineEdit * ForgotPasswordPanel::createLineEdit(WString label_)
{
    Wt::WLabel *label = new Wt::WLabel(label_);
    Wt::WLineEdit *edit = new Wt::WLineEdit("");
    edit->setTextSize(50);
    edit->setMaxLength(200);
    edit->setValidator(new Wt::WLengthValidator(0, 255));
    label->setBuddy(edit);

    int rowCount = _table->rowCount();
    _table->elementAt(rowCount, 0)->addWidget(label);
    _table->elementAt(rowCount, 1)->addWidget(edit);

    return edit;
}

WTextArea * ForgotPasswordPanel::createTextArea(WString label_)
{
    Wt::WLabel *label = new Wt::WLabel(label_);
    Wt::WTextArea *edit = new Wt::WTextArea("");
    edit->setColumns(42);
    edit->setRows(3);
    edit->setValidator(new Wt::WLengthValidator(0, 255));
    label->setBuddy(edit);

    int rowCount = _table->rowCount();
    _table->elementAt(rowCount, 0)->addWidget(label);
    _table->elementAt(rowCount, 1)->addWidget(edit);

    return edit;
}
