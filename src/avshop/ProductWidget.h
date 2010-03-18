#ifndef PRODUCTWIDGET_H
#define PRODUCTWIDGET_H
#include "string"
#include "Wt/WContainerWidget"
using namespace Wt;

#include "products/Product.h"

class ProductWidget : public WContainerWidget
{
public:
    ProductWidget(const Product * const product_);

public:
    void onBuyButton();

private:    
    const Product * _product;
};

#endif // PRODUCTWIDGET_H
