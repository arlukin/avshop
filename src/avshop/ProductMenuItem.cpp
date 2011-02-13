#include <Wt/WContainerWidget>
#include <Wt/WAnchor>
#include <Wt/WText>
#include "Wt/WCssDecorationStyle"
#include "Wt/WMenu"

#include "boost/lexical_cast.hpp"
#include "boost/regex.hpp"

#include "ProductWidget.h"
#include "ProductMenuItem.h"

ProductMenuItem::ProductMenuItem(const Product *product_)
    : WMenuItem::WMenuItem("", new ProductWidget(product_))
{
    _product = product_;    

    // Create a good looking url.
    const boost::regex e("[^0-9a-zA-Z]");
    std::string str = boost::regex_replace(_product->name(), e, "_");
    setPathComponent(str);    
}

WWidget *ProductMenuItem::createItemWidget()
{        
    //<div class="collection" style="background: url(productimages/QEES_Dimmer_billed_tekst_01_thumb.jpg) no-repeat;">
    WAnchor *result = new WAnchor();    
    WContainerWidget *collection = new WContainerWidget(result);
    result->mouseWentOver().connect(SLOT(this, ProductMenuItem::_mouseWentOver));
    result->mouseWentOut().connect(SLOT(this, ProductMenuItem::_mouseWentOut));

    collection->setStyleClass("collection");
    WString imageName = _product->imageThumbName("var/www/", "resources/images/productimages/");
    collection->decorationStyle().setBackgroundImage(imageName.toUTF8());

    _faderInvisible = new WContainerWidget(collection);
    _faderInvisible->setStyleClass("fader invisible");

    WContainerWidget *faderInvisible2 = new WContainerWidget(_faderInvisible);
    new WText(_description(), faderInvisible2);

    // @todo: Add this? Change picutre
    // <!--<div class="sale_label"></div>-->
    //WContainerWidget *salesLabel = new WContainerWidget(collection);
    //salesLabel->setStyleClass("sale_label");

    // @todo: Add this? Change picutre
    // <!--<div class="sale_label"></div>-->
    //WContainerWidget *offerLabel = new WContainerWidget(collection);
    //offerLabel->setStyleClass("offer_label");

  return result;
}

WString ProductMenuItem::_description()
{
    Wt:WString description
    (
        "<span class=\"heading\">" + _product->name() + "</span>"
        "<span class=\"price\">" + _product->salesPrice().amountFmt() + "</span>"
        "<span class=\"desc\">" + _product->description() + "</span>", UTF8
    );

    /*
        @todo: add for on sale.
        "<span class=\"price_sale\"><span>&pound;69.00</span></span>", UTF8);
    */

    return description;
}

void ProductMenuItem::_mouseWentOver()
{
    _faderInvisible->setStyleClass("fader");
}

void ProductMenuItem::_mouseWentOut()
{
    _faderInvisible->setStyleClass("fader invisible");
}
