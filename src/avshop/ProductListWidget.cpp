#include <Wt/WStackedWidget>
#include <Wt/WApplication>
#include <Wt/WAnchor>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WMenu>

#include "products/ProductTypes.h"

#include "ShopApplication.h"
#include "ProductListThumbViewWidget.h"
#include "ProductListWidget.h"

ProductListWidget::ProductListWidget()
{
    createSidePanel();
    createProductArea();
    createMenu();
}

void ProductListWidget::createSidePanel()
{
    _sidePanel = new WContainerWidget(this);
    _sidePanel->setStyleClass("side_panel");
}

void ProductListWidget::createProductArea()
{
    _content = new WStackedWidget(this);
    _content->setStyleClass("product_area");
}

void ProductListWidget::createMenu()
{
    new WText("<h1>Products</h1>", _sidePanel );
    new WText("<hr />", _sidePanel );
    WMenu *menu = new WMenu(_content, Wt::Vertical, _sidePanel );
    menu->setStyleClass("side_nav menu");
    //menu->setInternalPathEnabled();
    //menu->setInternalBasePath("/label_products");

    // Add menu items.
    ShopDb * db = ShopApplication::instance()->db();
    ProductTypes& productTypes = *(db->getProductTypes());

    productTypes.addFilter(ProductTypes::HAS_PRODUCTS);
    productTypes.load();
    for
    (
        ProductTypes::const_iterator productType = productTypes.begin();
        productType != productTypes.end();
        ++productType
    )
    {                    
        menu->addItem(WString(productType->name(), UTF8), new ProductListThumbViewWidget(productType->productTypeId(), _content));
    }
    menu->select(0);

    new WText("<hr />", _sidePanel );
}
