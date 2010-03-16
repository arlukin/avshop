#ifndef PRODUCTMENUITEM_H
#define PRODUCTMENUITEM_H

#include "Wt/WMenuItem"
using namespace Wt;

#include "products/Product.h"


class ProductMenuItem : public WMenuItem
{
public:
    ProductMenuItem(const Product *product_);

    void updateItemWidget(WWidget *itemWidget);
    WWidget *createItemWidget();

private:
    const Product * _product;
};

#endif // PRODUCTMENUITEM_H
