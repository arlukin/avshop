#ifndef SHOPAPPLICATION_H
#define SHOPAPPLICATION_H
#include <Wt/WApplication>
#include <Wt/WAnchor>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WMenuItem>

using namespace Wt;

#include "general/ShopDb.h"
#include "products/OrderHeader.h"
class CheckOutPanel;

class ShopApplication : public WApplication
{
public:
    ShopApplication(const WEnvironment& env);

    static ShopApplication * instance();
    void addToCart(const Product *product_);
    bool saveCart();
    OrderHeader & cart();
    User & user();

    Wt::WStackedWidget * getBody() { return _body; };

    ShopDb * db() { return &_shopDb; };

    void _onCheckOut();

private:
    void _createPage();
    void _createHeader(WContainerWidget *pageContainer_);
    void _createBody(WContainerWidget *pageContainer_);
    void _createFooter(WContainerWidget *pageContainer_);
    void _createCartBox(WContainerWidget *container_);

    void _createMenu();    
    void _createSidePanel();
    WContainerWidget* _createProductListThumbViewWidget(int productTypeId_);
    void _rebuildCart();

private:    
    OrderHeader _cart;
    User * _user;
    ShopDb _shopDb;    

    WContainerWidget *_mainNavContainer;
    WContainerWidget *_topNavContainer;
    WContainerWidget *_breadCrumbsContainer;

    Wt::WGroupBox *_memberBox;

    WContainerWidget * bodyContainer5;    
    Wt::WGroupBox *_sidePanel;
    Wt::WStackedWidget *_body;

    WContainerWidget *_footerRightContainer;    

    Wt::WMenuItem * _cartMenuItem;


    Wt::WComboBox *_cartCombo;
    WText * _cartTotalPrice;
    Wt::WPushButton *_cartCheckOut;

    Wt::WMenu *_mainMenu;
    WMenuItem * _showCart;
    CheckOutPanel * _checkOutPanel;
};

#endif // SHOPAPPLICATION_H
