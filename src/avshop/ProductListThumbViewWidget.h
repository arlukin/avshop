#ifndef PRODUCTLISTTHUMBVIEWWIDGET_H
#define PRODUCTLISTTHUMBVIEWWIDGET_H

#include <Wt/WContainerWidget>
using namespace Wt;

class ProductListThumbViewWidget : public WContainerWidget
{
public:
    ProductListThumbViewWidget(int productTypeId_, WStackedWidget *content_);
};

#endif // PRODUCTLISTTHUMBVIEWWIDGET_H
