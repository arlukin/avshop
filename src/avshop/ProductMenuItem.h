#ifndef PRODUCTMENUITEM_H
#define PRODUCTMENUITEM_H

#include "Wt/WString"
#include "Wt/WMenuItem"
using namespace Wt;

#include "products/Product.h"


class ProductMenuItem : public WMenuItem
{
public:
    ProductMenuItem(const Product *product_);

    WWidget* createItemWidget();

private:
    WString _description();
    void _mouseWentOver();
    void _mouseWentOut();

private:
    const Product* _product;

    WContainerWidget* _faderInvisible;
};

#endif // PRODUCTMENUITEM_H
