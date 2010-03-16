#ifndef FORGOTPASSWORDPANEL_H
#define FORGOTPASSWORDPANEL_H

#include "Wt/WString"
#include "Wt/WPanel"
#include "Wt/WLineEdit"
#include "Wt/WTextArea"
#include "Wt/WTable"
#include "Wt/WPushButton"
using namespace Wt;

class ForgotPasswordPanel : public WPanel
{
public:
    ForgotPasswordPanel();
private:
    WLineEdit * createLineEdit(WString label_);
    WTextArea * createTextArea(WString label_);
private:
    WContainerWidget * _container;
    WTable *_table;
    WPushButton * _okButton;
};

#endif // FORGOTPASSWORDPANEL_H
