#ifndef PRODUCTLISTWIDGET_H
#define PRODUCTLISTWIDGET_H

#include <Wt/WContainerWidget>
using namespace Wt;

class ProductListWidget : public WContainerWidget
{
public:
    ProductListWidget();

private:
    void createSidePanel();
    void createProductArea();
    void createMenu();
private:    

    WContainerWidget *_sidePanel;
    WStackedWidget *_content;
    WContainerWidget * _productArea;
};

#endif // PRODUCTLISTWIDGET_H
