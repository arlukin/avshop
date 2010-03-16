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

#include <boost/foreach.hpp>

#include "AVString.h"
#include "ShopApplication.h"
#include "ForgotPasswordPanel.h"
#include "NewAccountPanel.h"
#include "Widget/UserWidget.h"

#include "ShopApplication.h"
#include "CheckOutPanel/CheckOutPanel.h"
#include "CheckOutPanel/ConfirmPage.h"

ConfirmPage::ConfirmPage()
{
    setTitle("Confirm");
    setStyleClass("Wt-panel check_out_panel");

    refresh();
}

void ConfirmPage::refresh()
{
    WContainerWidget * container = new WContainerWidget();
    setCentralWidget(container);

    new WText(tr("check_out.intro"), container);

    _createCartGroup(container);
    _createUserGroup(container);
    //_createPaymentGroup(container);
    _createConfirmGroup(container);
    _createButtonContainer(container);
}

void ConfirmPage::_createCartGroup(WContainerWidget * container_)
{
    Wt::WGroupBox *cartGroup = new Wt::WGroupBox(tr("check_out.cart_label"), container_);

    Wt::WTable *table = new Wt::WTable(cartGroup);
    table->setStyleClass("check_out_cart_table");
    table->setHeaderCount(1);
    table->elementAt(0, 0)->addWidget(new Wt::WText(tr("check_out.quantity")));
    table->elementAt(0, 1)->addWidget(new Wt::WText(tr("check_out.product_name")));
    table->elementAt(0, 2)->addWidget(new Wt::WText(tr("check_out.in_stock")));
    table->elementAt(0, 3)->addWidget(new Wt::WText(tr("check_out.unit_price")));
    table->elementAt(0, 4)->addWidget(new Wt::WText(tr("check_out.total")));

    int row = 1;

    OrderHeader cart = ShopApplication::instance()->cart();
    BOOST_FOREACH(OrderHeader::t_OrderRow orderRows, cart.orderRows())
    {
        const OrderRow &cartItem = orderRows.second;
        table->elementAt(row, 0)->addWidget(new Wt::WText(avitos(cartItem.number())));
        table->elementAt(row, 1)->addWidget(new Wt::WText(cartItem.product().name()));
        table->elementAt(row, 2)->addWidget(new Wt::WText(avitos(cartItem.product().deliveryTime())));
        table->elementAt(row, 3)->addWidget(new Wt::WText(cartItem.product().salesPrice().amountFmt()));
        table->elementAt(row, 4)->addWidget(new Wt::WText(cartItem.totalSalesPrice().amountFmt()));
        row++;
    }

    // Total
    table->elementAt(row, 0)->setColumnSpan(2);
    table->elementAt(row, 2)->addWidget(new Wt::WText(tr("check_out.total_cart_value")));
    table->elementAt(row, 2)->setColumnSpan(2);
    table->elementAt(row, 4)->addWidget(new Wt::WText(cart.totalSalesPrice().amountFmt()));
    row++;

    table->elementAt(row, 0)->setColumnSpan(2);
    table->elementAt(row, 2)->addWidget(new Wt::WText(tr("check_out.shipping")));
    table->elementAt(row, 2)->setColumnSpan(2);
    table->elementAt(row, 4)->addWidget(new Wt::WText("0 kr"));
    row++;

    table->elementAt(row, 0)->setColumnSpan(2);
    table->elementAt(row, 2)->addWidget(new Wt::WText(tr("check_out.total_ex_vat")));
    table->elementAt(row, 2)->setColumnSpan(2);
    Wt::WText * _total = new Wt::WText(cart.totalSalesPrice().amountFmt());
    table->elementAt(row, 4)->addWidget(_total);

    for(int row=0;row < table->rowCount();row++)
    {
        for(int column=0;column < table->columnCount();column++)
        {
            std::stringstream className;
            className << "col" << column;
            className << " " << table->elementAt(row, column)->styleClass();
            table->elementAt(row, column)->setStyleClass(className.str());
        }
    }
}

void ConfirmPage::_createUserGroup(WContainerWidget * container_)
{
    Wt::WGroupBox* _loginGroup = new Wt::WGroupBox(tr("check_out.your_information"), container_);
    _loginGroup->addWidget(new UserWidget(true));
}

 void ConfirmPage::_createPaymentGroup(WContainerWidget * container_)
 {
    // Payment method
    /*
    Wt::WGroupBox *paymentGroup = new Wt::WGroupBox("Payment method", container);
    new WText("Credit card", paymentGroup);
    */

    Wt::WGroupBox *paymentGroup = new Wt::WGroupBox(tr("payment.payment_methd"), container_);
    Wt::WRadioButton *creditCardButton = new Wt::WRadioButton(tr("payment.credit_card"), paymentGroup);
    Wt::WRadioButton *payPalButton = new Wt::WRadioButton(tr("check_out.pay_pal"), paymentGroup);

    enum Vote { CreditCard = 1, PayPal = 2};
    Wt::WButtonGroup *group = new Wt::WButtonGroup(this);
    group->addButton(creditCardButton, CreditCard);
    group->addButton(payPalButton, PayPal);
    group->setCheckedButton(creditCardButton);
}

void ConfirmPage::_createConfirmGroup(WContainerWidget * container_)
{
    Wt::WGroupBox *confirmGroup = new Wt::WGroupBox(tr("check_out.confirm"), container_);

    //if (termsCheck->checked())
    new Wt::WText(tr("check_out.accept_terms_and_cond"), confirmGroup);
    new WBreak(confirmGroup);
    //if (deliveryCheck->checked())
    //new Wt::WText(tr("check_out.part_deliver"), confirmGroup);
  }

 void ConfirmPage::_createButtonContainer(WContainerWidget * container_)
 {
    // Next button
    new Wt::WText("<hr />", container_);
    WContainerWidget * buttonContainer = new WContainerWidget(container_);
    buttonContainer->setStyleClass("buttoncontainer_");

    CheckOutPanel * checkOutPanel = dynamic_cast<CheckOutPanel*>(parent());

    WPushButton* prevButton = new Wt::WPushButton(WString::tr("button.prev"), buttonContainer);
    prevButton->clicked().connect(SLOT(this, ConfirmPage::_onPrev));

    WPushButton* completeButton = new Wt::WPushButton(WString::tr("button.complete"), buttonContainer);
    completeButton->clicked().connect(SLOT(this, ConfirmPage::_onComplete));
}

WLineEdit * ConfirmPage::createLineEdit(WString label_, Wt::WContainerWidget *group_)
{
    Wt::WLabel *label = new Wt::WLabel(label_, group_);
    Wt::WLineEdit *edit = new Wt::WLineEdit("", group_);
    edit->setTextSize(50);
    edit->setMaxLength(200);
    edit->setValidator(new Wt::WLengthValidator(0, 255));
    label->setBuddy(edit);

    return edit;
}

void ConfirmPage::_onPrev()
{
    CheckOutPanel * checkOutPanel = dynamic_cast<CheckOutPanel*>(parent());
    checkOutPanel->goToCheckOutPage();
}

void ConfirmPage::_onComplete()
{
    if (ShopApplication::instance()->saveCart())
    {
        CheckOutPanel * checkOutPanel = dynamic_cast<CheckOutPanel*>(parent());
        checkOutPanel->goToCompletedPage();
    }
}
