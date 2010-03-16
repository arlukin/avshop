#ifndef USERWIDGET_H
#define USERWIDGET_H

#include "Wt/WString"
#include "Wt/WPanel"
#include "Wt/WLineEdit"
#include "Wt/WTextArea"
#include "Wt/WTable"
#include "Wt/WPushButton"
using namespace Wt;

class UserWidget : public WContainerWidget
{
public:
    UserWidget(bool readOnly_ = false);
    void fetchErrorMessages(Wt::WContainerWidget * errorMessages_);
    void storeInModel();
private:
    enum {PASSWORD = 1};

    WLineEdit * createLineEdit(WString label_, WString default_ = "", int flags_ = 0);
    WTextArea * createTextArea(WString label_, WString default_ = "");
private:    
    bool _readOnly;

    WTable *_table;

    WLineEdit * _userName;
    WLineEdit * _password;
    WLineEdit * _confirmPassword;

    WLineEdit * _firstName;
    WLineEdit * _lastName;
    WLineEdit * _companyName;
    WTextArea * _address;
    WLineEdit * _zip;
    WLineEdit * _city;
    WLineEdit * _phone;
    WLineEdit * _email;
    WLineEdit * _web;
};

#endif // USERWIDGET_H
