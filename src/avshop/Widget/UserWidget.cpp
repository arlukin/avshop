#include "Wt/WLengthValidator"
#include "Wt/WLabel"
#include "Wt/WContainerWidget"
#include "Wt/WBreak"
#include "Wt/WText"

#include "user/User.h"
using namespace av;

#include "ShopApplication.h"
#include "Widget/UserWidget.h"

UserWidget::UserWidget(bool readOnly_)
{
    _readOnly = readOnly_;

    setStyleClass("user_widget");

    _table = new Wt::WTable(this);

    User& user = ShopApplication::instance()->user();

    _userName = createLineEdit("User name:", user.userName());
    _password = createLineEdit("Password:", "", PASSWORD);
    _confirmPassword = createLineEdit("Confirm password:", "", PASSWORD);

    Contact& orginator = user.contact();
    _firstName = createLineEdit("First name:", orginator.firstName());
    _lastName = createLineEdit("Last name:", orginator.lastName());
    _companyName = createLineEdit("Company name:", orginator.companyName());
    _address = createTextArea("Address:", orginator.address());
    _zip = createLineEdit("Zip:", orginator.zip());
    _city = createLineEdit("City:", orginator.city());
    _phone = createLineEdit("Phone:", orginator.phone());
    _email = createLineEdit("email:", orginator.email());
    _web = createLineEdit("web:", orginator.webUrl());
}

void UserWidget::fetchErrorMessages(Wt::WContainerWidget * errorMessages_)
{
    if (_confirmPassword->text() != _password->text())
    {
        errorMessages_->addWidget(new Wt::WText(tr("user_widget.error.notMatchingPassword")));
        errorMessages_->addWidget(new Wt::WBreak());
    }
}

void UserWidget::storeInModel()
{
    User& user = ShopApplication::instance()->user();

    user.setUserName(_userName->text().toUTF8());
    user.setPassword(_password->text().toUTF8());

    Contact& orginator = user.contact();

    orginator.setFirstName(_firstName->text().toUTF8());
    orginator.setLastName(_lastName->text().toUTF8());
    orginator.setCompanyName(_companyName->text().toUTF8());
    orginator.setAddress(_address->text().toUTF8());
    orginator.setZip(_zip->text().toUTF8());
    orginator.setCity(_city->text().toUTF8());
    orginator.setPhone(_phone->text().toUTF8());
    orginator.setEmail(_email->text().toUTF8());
    orginator.setWebUrl(_web->text().toUTF8());
}

WLineEdit * UserWidget::createLineEdit(WString label_, WString default_, int flags_)
{
    Wt::WLabel *label = new Wt::WLabel(label_);

    Wt::WLineEdit *edit = new Wt::WLineEdit(default_);
    edit->setTextSize(50);
    edit->setMaxLength(200);
    edit->setValidator(new Wt::WLengthValidator(0, 255));
    label->setBuddy(edit);

    if (flags_ == PASSWORD)
    {
        edit->setEchoMode(WLineEdit::Password);
    }

    if (_readOnly)
    {
        edit->setReadOnly(true);
    }

    int rowCount = _table->rowCount();
    _table->elementAt(rowCount, 0)->addWidget(label);
    _table->elementAt(rowCount, 1)->addWidget(edit);

    return edit;
}

WTextArea * UserWidget::createTextArea(WString label_, WString default_)
{
    Wt::WLabel *label = new Wt::WLabel(label_);

    Wt::WTextArea *edit = new Wt::WTextArea(default_);
    edit->setColumns(42);
    edit->setRows(3);
    edit->setValidator(new Wt::WLengthValidator(0, 255));
    label->setBuddy(edit);

    if (_readOnly)
    {
        edit->setReadOnly(true);
    }

    int rowCount = _table->rowCount();
    _table->elementAt(rowCount, 0)->addWidget(label);
    _table->elementAt(rowCount, 1)->addWidget(edit);

    return edit;
}
