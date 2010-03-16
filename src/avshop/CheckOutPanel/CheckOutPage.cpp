#include "Wt/WContainerWidget"
#include "Wt/WMenu"
#include "Wt/WTable"
#include "Wt/WLengthValidator"
#include "Wt/WLabel"
#include "Wt/WBreak"
#include "Wt/WText"
#include "Wt/WImage"
#include "Wt/WCheckBox"
#include "Wt/WButtonGroup"
#include "Wt/WRadioButton"

#include <boost/foreach.hpp>

#include "AVString.h"
#include "user/User.h"
#include "user/ActionGroup.h"
using namespace av;


#include "ShopApplication.h"
#include "ForgotPasswordPanel.h"
#include "NewAccountPanel.h"
#include "CheckOutPanel.h"
#include "CheckOutPage.h"

CheckOutPage::CheckOutPage()
    : _userWidget(0)
{
    setTitle("Check out");
    setStyleClass("Wt-panel check_out_panel");

    refresh();
}

void CheckOutPage::refresh()
{
    WContainerWidget * container = new WContainerWidget();
    setCentralWidget(container);

    new WText(tr("check_out.intro"), container);

    _createCartGroup(container);
    _createLoginGroup(container);
    //_createPaymentGroup(container);
    _createConfirmGroup(container);
    _createButtonContainer(container);
}

void CheckOutPage::_createCartGroup(WContainerWidget * container_)
{
    Wt::WGroupBox *cartGroup = new Wt::WGroupBox(tr("check_out.cart_label"), container_);

    _productTable = new Wt::WTable(cartGroup);
    _productTable->setStyleClass("check_out_cart_table");
    _productTable->setHeaderCount(1);

    _productTable->elementAt(0, 0)->addWidget(new Wt::WText(tr("check_out.quantity")));
    _productTable->elementAt(0, 1)->addWidget(new Wt::WText(tr("check_out.product_name")));
    _productTable->elementAt(0, 2)->addWidget(new Wt::WText(tr("check_out.in_stock")));
    _productTable->elementAt(0, 3)->addWidget(new Wt::WText(tr("check_out.unit_price")));
    _productTable->elementAt(0, 4)->addWidget(new Wt::WText(tr("check_out.total")));

    int row = 1;
    OrderHeader cart = ShopApplication::instance()->cart();
    BOOST_FOREACH(OrderHeader::t_OrderRow orderRows, cart.orderRows())
    {
        const OrderRow &orderRow = orderRows.second;
        Wt::WLineEdit * quantity = new Wt::WLineEdit(avitos(orderRow.number()));
        quantity->blurred().connect(SLOT(this, CheckOutPage::_onUpdate));
        _productTable->elementAt(row, 0)->addWidget(quantity);
        _productTable->elementAt(row, 0)->setStyleClass("check_out_quantity_edit");
        _productTable->elementAt(row, 1)->addWidget(new Wt::WText(orderRow.product().name()));
        _productTable->elementAt(row, 2)->addWidget(new Wt::WText(avitos(orderRow.product().deliveryTime())));
        _productTable->elementAt(row, 3)->addWidget(new Wt::WText(orderRow.product().salesPrice().amountFmt()));
        _productTable->elementAt(row, 4)->addWidget(new Wt::WText(orderRow.totalSalesPrice().amountFmt()));
        row++;
    }

    // Total Excluding Shipping
    _productTable->elementAt(row, 0)->setColumnSpan(2);
    _productTable->elementAt(row, 2)->addWidget(new Wt::WText(tr("check_out.total_cart_value")));
    _productTable->elementAt(row, 2)->setColumnSpan(2);
    _totalExShipping = new Wt::WText();
    _productTable->elementAt(row, 4)->addWidget(_totalExShipping);
    row++;    

    // Shipping
    _productTable->elementAt(row, 0)->setColumnSpan(2);
    _productTable->elementAt(row, 2)->addWidget(new Wt::WText(tr("check_out.shipping")));
    _productTable->elementAt(row, 2)->setColumnSpan(2);
    _productTable->elementAt(row, 4)->addWidget(new Wt::WText("0 kr"));
    row++;

    // Total including shipping
    Wt::WPushButton * updateButton = new Wt::WPushButton(WString::tr("button.update"));
    _productTable->elementAt(row, 0)->addWidget(updateButton);
    _productTable->elementAt(row, 0)->setColumnSpan(2);
    _productTable->elementAt(row, 2)->addWidget(new Wt::WText(tr("check_out.total_ex_vat")));
    _productTable->elementAt(row, 2)->setColumnSpan(2);
    _total = new Wt::WText();
    _productTable->elementAt(row, 4)->addWidget(_total);

    updateButton->clicked().connect(SLOT(this, CheckOutPage::_onUpdate));

    for(int row=0;row < _productTable->rowCount();row++)
    {
        for(int column=0;column < _productTable->columnCount();column++)
        {
            std::stringstream className;
            className << "col" << column;
            className << " " << _productTable->elementAt(row, column)->styleClass();
            _productTable->elementAt(row, column)->setStyleClass(className.str());
        }
    }

    _rebuildCartPrices();
}

void CheckOutPage::_createLoginGroup(WContainerWidget * container_)
{
    _loginGroup = new Wt::WGroupBox(tr("check_out.your_information"), container_);

    User& user = ShopApplication::instance()->user();
    if (user.isLoggedIn())
    {
        _userWidget = new UserWidget();
        _loginGroup->addWidget(_userWidget);
    }
    else
    {
        _loginGroup->addWidget(_createLoginWidget());
    }
}

WContainerWidget * CheckOutPage::_createLoginWidget()
{
    WContainerWidget * container = new WContainerWidget();
    _userNameEdit = createLineEdit(tr("check_out.user_name"), container);
    _passwordEdit = createLineEdit(tr("check_out.password"), container);
    _passwordEdit->setEchoMode(WLineEdit::Password);
    _loginButton = new Wt::WPushButton(WString::tr("button.ok"), container);
    _loginButton->clicked().connect(SLOT(this, CheckOutPage::_onLogin));

    new WBreak(container);

    _loginErrorMessage = new Wt::WText(container);
    _loginErrorMessage->setStyleClass("error");

    new WBreak(container);

    Wt::WMenu *loginMenu = new Wt::WMenu(ShopApplication::instance()->getBody(), Wt::Horizontal, container);
    loginMenu->setStyleClass("menu");
    loginMenu->addItem(tr("check_out.forgot_password"), new ForgotPasswordPanel());
    loginMenu->addItem(tr("check_out.register_new_account"), new NewAccountPanel());
    //loginMenu->setInternalPathEnabled();

    return container;
}

void CheckOutPage::_createPaymentGroup(WContainerWidget * container_)
{
    Wt::WGroupBox *paymentGroup = new Wt::WGroupBox(tr("payment.payment_methd"), container_);
    Wt::WRadioButton *creditCardButton = new Wt::WRadioButton(tr("payment.credit_card"), paymentGroup);
    Wt::WRadioButton *payPalButton = new Wt::WRadioButton(tr("check_out.pay_pal"), paymentGroup);

    enum Vote { CreditCard = 1, PayPal = 2};
    Wt::WButtonGroup *group = new Wt::WButtonGroup(this);
    group->addButton(creditCardButton, CreditCard);
    group->addButton(payPalButton, PayPal);
    group->setCheckedButton(creditCardButton);
}

void CheckOutPage::_createConfirmGroup(WContainerWidget * container_)
{
    Wt::WGroupBox *confirmGroup = new Wt::WGroupBox(tr("check_out.confirm"), container_);

    _termsCheck = new Wt::WCheckBox(tr("check_out.accept_terms_and_cond"), confirmGroup);
    //new WBreak(confirmGroup);
    //_deliveryCheck = new Wt::WCheckBox(tr("check_out.part_deliver"), confirmGroup);

    _termsCheck->setChecked(false);
    //_deliveryCheck->setChecked(false);
}

void CheckOutPage::_createButtonContainer(WContainerWidget * container_)
{
    // Ok button
    new Wt::WText("<hr />", container_);
    _errorMessages = new Wt::WContainerWidget(container_);
    _errorMessages->setStyleClass("error");
    WContainerWidget * buttonContainer = new WContainerWidget(container_);
    buttonContainer->setStyleClass("buttoncontainer_");    

    CheckOutPanel * checkOutPanel = dynamic_cast<CheckOutPanel*>(parent());
    _nextButton = new Wt::WPushButton(WString::tr("button.next"), buttonContainer);
    _nextButton->clicked().connect(SLOT(this, CheckOutPage::_onNext));
}

WLineEdit * CheckOutPage::createLineEdit(WString label_, Wt::WContainerWidget *group_)
{
    Wt::WLabel *label = new Wt::WLabel(label_, group_);
    Wt::WLineEdit *edit = new Wt::WLineEdit("", group_);
    edit->setTextSize(50);
    edit->setMaxLength(200);
    edit->setValidator(new Wt::WLengthValidator(0, 255));
    label->setBuddy(edit);

    return edit;
}

void CheckOutPage::_updateCartModel()
{
    OrderHeader &cart = ShopApplication::instance()->cart();
    for(int row = 1; row < _productTable->rowCount()-3; row++)
    {
        Wt::WLineEdit * edit = dynamic_cast<Wt::WLineEdit*>(_productTable->elementAt(row, 0)->widget(0));
        Wt::WText * productName = dynamic_cast<Wt::WText*>(_productTable->elementAt(row, 1)->widget(0));
        cart.orderRows().at(productName->text().toUTF8()).setNumber(avstoi(edit->text().toUTF8()));
    }
}

void CheckOutPage::_rebuildCartPrices()
{
    OrderHeader& cart = ShopApplication::instance()->cart();

    for(int row = 1; row < _productTable->rowCount()-3; row++)
    {
        Wt::WText * productName = dynamic_cast<Wt::WText*>(_productTable->elementAt(row, 1)->widget(0));
        const OrderRow &orderRow = cart.orderRows().at(productName->text().toUTF8());

        Wt::WText * total = dynamic_cast<Wt::WText*>(_productTable->elementAt(row, 4)->widget(0));
        total->setText(orderRow.totalSalesPrice().amountFmt());
    }

    _totalExShipping->setText(cart.totalSalesPrice().amountFmt());
    _total->setText(cart.totalSalesPrice().amountFmt());
}

bool CheckOutPage::isPageValid()
{
    _errorMessages->clear();    
    User& user = ShopApplication::instance()->user();
    if (!user.isLoggedIn())
    {
        _errorMessages->addWidget(new Wt::WText(tr("check_out.error.need_to_login")));
        _errorMessages->addWidget(new Wt::WBreak());
    }

    if (!_termsCheck->isChecked())
    {
        _errorMessages->addWidget(new Wt::WText(tr("check_out.error.need_to_accept_t_and_c")));
        _errorMessages->addWidget(new Wt::WBreak());
    }

    if (_userWidget)
    {
        _userWidget->fetchErrorMessages(_errorMessages);
    }

    return _errorMessages->count() == 0;
}

void CheckOutPage::_onUpdate()
{
    _updateCartModel();
    _rebuildCartPrices();
}

void CheckOutPage::_onLogin()
{    
    User& user = ShopApplication::instance()->user();
    if (user.login(_userNameEdit->text().toUTF8(), _passwordEdit->text().toUTF8()))
    {
        _loginGroup->clear();
        _userWidget = new UserWidget();
        _loginGroup->addWidget(_userWidget);
    }
    else
    {
        _loginErrorMessage->setText(tr("check_out.error.login"));
    }
}

void CheckOutPage::_onNext()
{
    if (isPageValid())
    {
        _userWidget->storeInModel();
        CheckOutPanel * checkOutPanel = dynamic_cast<CheckOutPanel*>(parent());
        checkOutPanel->goToConfirmPage();
    }
}
