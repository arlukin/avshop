#include <Wt/WAnchor>
#include <Wt/WText>
#include "Wt/WCssDecorationStyle"
#include "Wt/WMenu"

#include "general/ShopDb.h"
#include "products/Products.h"

#include "ProductWidget.h"
#include "ProductMenuItem.h"
#include "ProductListThumbViewWidget.h"

ProductListThumbViewWidget::ProductListThumbViewWidget(int productTypeId_, WStackedWidget *content_)
{        
    WMenu *menu = new WMenu(content_, Wt::Horizontal, this );
    //menu->setInternalPathEnabled();
    //menu->setInternalBasePath("daniel");

    ShopDb shopDb;
    Products& products = *shopDb.getProducts();

    products.load(productTypeId_);
    for (Products::const_iterator productIt = products.begin();
        productIt != products.end();
        ++productIt)
    {
        Product const &product = *productIt;

        menu->addItem(new ProductMenuItem(&product));
    }
}
