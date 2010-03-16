#ifndef CHECKOUTPAGE_H
#define CHECKOUTPAGE_H

#include "Wt/WGroupBox"
#include "Wt/WPanel"
#include "Wt/WTable"
#include "Wt/WLineEdit"
#include "Wt/WTextArea"
#include "Wt/WPushButton"
#include "Wt/WString"
using namespace Wt;

#include "Widget/UserWidget.h"

class CheckOutPage : public WPanel
{
public:
    CheckOutPage();

    void refresh();
private:
    WContainerWidget * createEditPage();
    void _createCartGroup(WContainerWidget * container_);
    void _createLoginGroup(WContainerWidget * container_);
    WContainerWidget* _createLoginWidget();
    void _createPaymentGroup(WContainerWidget * container_);
    void _createConfirmGroup(WContainerWidget * container_);
    void _createButtonContainer(WContainerWidget * container_);

    WLineEdit * createLineEdit(WString label_, Wt::WContainerWidget *group_);

    void _updateCartModel();
    void _rebuildCartPrices();
    bool isPageValid();

    void _onUpdate();    
    void _onLogin();
    void _onNext();    

private:
    Wt::WTable *_productTable;
    Wt::WGroupBox   * _loginGroup;
    Wt::WLineEdit   * _userNameEdit;
    Wt::WLineEdit   * _passwordEdit;
    Wt::WPushButton * _loginButton;
    Wt::WText       * _loginErrorMessage;

    UserWidget * _userWidget;

    Wt::WCheckBox *_termsCheck;
    Wt::WCheckBox *_deliveryCheck;

    Wt::WContainerWidget * _errorMessages;
    WPushButton * _nextButton;

    WText * _totalExShipping;
    WText * _total;
};

#endif // CHECKOUTPAGE_H
