#include <boost/foreach.hpp>
#include <boost/algorithm/string/case_conv.hpp>

#include <Wt/WEnvironment>
#include <Wt/WStackedWidget>
#include <Wt/WMenu>
#include "Wt/WGroupBox"
#include "Wt/WComboBox"
#include "Wt/WImage"
#include "Wt/WButtonGroup"
#include "Wt/WRadioButton"
#include "Wt/WLogger"
using namespace Wt;

#include "products/Product.h"
#include "user/User.h"
#include "user/ActionGroup.h"
using namespace av;

#include "ShopApplication.h"
#include "ProductListWidget.h"
#include "ArticleWidget.h"
#include "Widget/UserWidget.h"
#include "ForgotPasswordPanel.h"
#include "CheckOutPanel/CheckOutPanel.h"

ShopApplication::ShopApplication(const WEnvironment& env)
    : WApplication(env), _user(0), _checkOutPanel(0)
{
    _createPage();
}

ShopApplication * ShopApplication::instance()
{
    return dynamic_cast<ShopApplication *>(WApplication::instance());
}

void ShopApplication::addToCart(const Product *product_)
{
    _cart.addProduct(*product_);    
    _rebuildCart();
}

bool ShopApplication::saveCart()
{
    user().save();
    cart().orginator() = user().contact();
    cart().save(*db()->getSession());
    cart().clear();
    _rebuildCart();

    return true;
}

OrderHeader & ShopApplication::cart()
{
    return _cart;
}

User & ShopApplication::user()
{
    if (_user == 0)
    {
        _user = db()->getUser();
    }

    return *_user;
}

void ShopApplication::_onCheckOut()
{
    if (_checkOutPanel == 0)
    {
        _checkOutPanel = new CheckOutPanel();
        _body->addWidget(_checkOutPanel);
    }
    _body->setCurrentWidget(_checkOutPanel);
    _checkOutPanel->refresh();
}

void ShopApplication::_createPage()
{
    setTitle("Amivono shop");
    useStyleSheet("/resources/css/style.css");    
    messageResourceBundle().use("etc/avshop", false);

    _createHeader(root());
    _createBody(root());
    _createFooter(root());

    _createMenu();
}

void ShopApplication::_createHeader(WContainerWidget *pageContainer_)
{
    // Heading
    WContainerWidget *headerContainer = new WContainerWidget(pageContainer_);
    headerContainer->setStyleClass("header");

    // Logo
    WContainerWidget *logoContainer = new WContainerWidget(headerContainer);
    logoContainer->setStyleClass("logo");
    new WAnchor("/", WString::tr("logo.slogan"), logoContainer);

    // Cart
    _createCartBox(headerContainer);

    // Bread crumbs
    _breadCrumbsContainer = new WContainerWidget(headerContainer);
    _breadCrumbsContainer->setStyleClass("bread_crumbs");

    // Main nav
    _mainNavContainer = new WContainerWidget(headerContainer);
    _mainNavContainer->setStyleClass("navigation");
}

void ShopApplication::_createBody(WContainerWidget *pageContainer_)
{    
    WContainerWidget *bodyContainer = new WContainerWidget(pageContainer_);
    bodyContainer->setStyleClass("body_back_top");

    WContainerWidget *bodyContainer1 = new WContainerWidget(bodyContainer);
    bodyContainer1->setStyleClass("body_back_bottom");

    WContainerWidget *bodyContainer2 = new WContainerWidget(bodyContainer1);
    bodyContainer2->setStyleClass("body_top");

    WContainerWidget *bodyContainer3 = new WContainerWidget(bodyContainer2);
    bodyContainer3->setStyleClass("body_bottom");

    WContainerWidget *bodyContainer4 = new WContainerWidget(bodyContainer3);
    bodyContainer4->setStyleClass("body_content");

    bodyContainer5 = new WContainerWidget(bodyContainer4);

    _body = new Wt::WStackedWidget(bodyContainer5);
}

void ShopApplication::_createFooter(WContainerWidget *pageContainer_)
{
    WContainerWidget *footerContainer = new WContainerWidget(pageContainer_);
    footerContainer->setStyleClass("footer");

    // Footer left
    WText *footerLeft = new WText(WString::tr("footer.copyright"), footerContainer);
    footerLeft->setStyleClass("footer_left");

    // Footer right
    _footerRightContainer = new WContainerWidget(footerContainer);
    _footerRightContainer->setStyleClass("footer_right");
}

void ShopApplication::_createCartBox(WContainerWidget *container_)
{
    // Cart container
    Wt::WGroupBox *cartBox = new Wt::WGroupBox("", container_);
    cartBox->setStyleClass("cart_box");

    // Cart image
    WContainerWidget *cartImage= new WContainerWidget(cartBox);
    cartImage->setStyleClass("cart_image");
    new WText(WString::tr("cart.tooltip"), cartImage);

    _cartCombo = new Wt::WComboBox(cartBox);

    _cartCheckOut = new Wt::WPushButton(WString::tr("cart.check_out"), cartBox);
    _cartCheckOut->clicked().connect(SLOT(this, ShopApplication::_onCheckOut));
    new Wt::WBreak(cartBox);

    WText * total = new WText(WString::tr("cart.total"), cartBox);
    total->setStyleClass("cart_total");
    _cartTotalPrice = new WText(cartBox);

    // VAT type
    enum Vat { EXVAT= 1, INCVAT= 2};
    Wt::WButtonGroup *group = new Wt::WButtonGroup(this);

    /*
    Wt::WRadioButton *button;
    button = new Wt::WRadioButton(WString::tr("cart.ex_vat"), cartBox);
    group->addButton(button, EXVAT);

    button = new Wt::WRadioButton(WString::tr("cart.inc_vat"), cartBox);
    group->addButton(button, INCVAT);

    group->setCheckedButton(group->button(EXVAT));
    */

    _rebuildCart();
}

WString upperTr(const std::string& string_)
{
    std::string str = WString::tr(string_).toUTF8();
    std::string upperStr = boost::to_upper_copy(str);

    return WString(upperStr, UTF8);
}

void ShopApplication::_createMenu()
{    
    // Main Menu
    _mainMenu = new Wt::WMenu(_body, Wt::Horizontal, _mainNavContainer);    
    _mainMenu->setRenderAsList(true);
    _mainMenu->setStyleClass("menu main_menu");
    _mainMenu->setInternalPathEnabled();    

    // Will be sorted backwards.
    _mainMenu->addItem(upperTr("about_us"), new ArticleWidget("footer.about_us"));
    _mainMenu->addItem(upperTr("contact_us"), new ArticleWidget("footer.contact_us"));
    _mainMenu->addItem(upperTr("faq"), new ArticleWidget("footer.faq"));
    _mainMenu->addItem(upperTr("products"), new ProductListWidget());

    // Breadcrumb menu
    //Wt::WMenu *breadCrumbMenu = new Wt::WMenu(_body, Wt::Horizontal, _breadCrumbsContainer);
    //breadCrumbMenu->setStyleClass("menu");
    /*
    breadCrumbMenu->addItem("Hem /", new ArticleWidget("mainnav.Produkter"));
    breadCrumbMenu->addItem("Produkter /", new ArticleWidget("mainnav.Inspiration"));
    breadCrumbMenu->setInternalPathEnabled();
    */

    // Footer menu
    //Wt::WMenu *footerMenu  = new Wt::WMenu(_body, Wt::Horizontal, _footerRightContainer);
    //footerMenu->setStyleClass("menu");
    //footerMenu->addItem("Inspiration", new ArticleWidget("mainnav.Inspiration"));
    //footerMenu->addItem("Artiklar", new ArticleWidget("mainnav.Artiklar"));
    //footerMenu->addItem(WString::tr("label.sitemap"), new ArticleWidget("footer.sitemap"));
    //footerMenu->setInternalPathEnabled();
}

void ShopApplication::_rebuildCart()
{
    _cartCombo->clear();

    if (_cart.orderRows().size() == 0)
    {
        _cartCombo->addItem(WString::tr("cart.shopping_cart_is_empty"));

        _cartTotalPrice->setText("0 SEK");
    }
    else
    {
        BOOST_FOREACH(OrderHeader::t_OrderRow orderRow, _cart.orderRows())
        {
            _cartCombo->addItem(orderRow.second.cartName());
        }

        _cartTotalPrice->setText(_cart.totalSalesPrice().amountFmt());
    }    
}

/*
  @todo: Add this
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta name="description" content="Denna beskrivning visas ganska ofta i sökresultaten, 40 och 150 tecken" />
    <meta name="keywords" content="" />
    <meta name="author" content="Daniel Lindh, aka Arlukin, aka Master Po" />
    <meta name="robots" content="index, follow" />
    <link rel="icon" href="favicon.ico" type="image/x-icon" />
    <link rel="shortcut icon" href="favicon.ico" type="image/x-icon" />
</head>
 */
