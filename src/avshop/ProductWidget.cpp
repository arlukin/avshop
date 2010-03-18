#include <locale>

#include "Wt/WImage"
#include "Wt/WText"
#include "Wt/WGroupBox"
#include "Wt/WTable"
#include "Wt/WPushButton"
#include "Wt/WBreak"

#include "ShopApplication.h"
#include "ProductWidget.h"

ProductWidget::ProductWidget(const Product * const product_)
{
    _product = product_;
    setStyleClass("product");

    new WText("<h1>" + _product->name() + "</h1>", this);

    Wt::WImage *img = new Wt::WImage(_product->imageName("var/www/", "resources/images/productimages/"), this);
    img->setAlternateText(_product->name());
    img->setStyleClass("product_image");    

    Wt::WGroupBox *container = new Wt::WGroupBox("", this);

    // Price
    WText * price = new WText(_product->salesPrice().amountFmt(), container);
    price->setStyleClass("product_price");

    // Köp
    WPushButton *ok = new Wt::WPushButton(WString::tr("button.buy"), container);
    ok->clicked().connect(SLOT(this, ProductWidget::onBuyButton));

    // Specifications
    Wt::WTable *table = new Wt::WTable(container);
    table->elementAt(0, 0)->addWidget(new Wt::WText(WString::tr("label.type")));
    table->elementAt(0, 1)->addWidget(new Wt::WText("Remote"));

    table->elementAt(1, 0)->addWidget(new Wt::WText(WString::tr("label.manufacture")));
    table->elementAt(1, 1)->addWidget(new Wt::WText("Vera"));

    table->elementAt(2, 0)->addWidget(new Wt::WText(WString::tr("label.product_no")));
    table->elementAt(2, 1)->addWidget(new Wt::WText("IN100"));

    table->elementAt(3, 0)->addWidget(new Wt::WText(WString::tr("label.delivery_time")));
    table->elementAt(3, 1)->addWidget(new Wt::WText("2-3 weeks"));

    // Info
    new WBreak(this);
    const std::string desc = _product->description();    
    WText * body = new WText(WString(desc, UTF8), this);
    body->setStyleClass("product_text");
}

void ProductWidget::onBuyButton()
{    
    ShopApplication::instance()->addToCart(_product);
}
