#include <Wt/WContainerWidget>
#include <Wt/WAnchor>
#include <Wt/WText>
#include "Wt/WCssDecorationStyle"
#include "Wt/WMenu"

#include "ProductWidget.h"
#include "ProductMenuItem.h"

ProductMenuItem::ProductMenuItem(const Product *product_)
    : WMenuItem::WMenuItem(product_->imageThumbName("var/www/", "resources/images/productimages/"), new ProductWidget(product_), PreLoading)
{
    _product = product_;
    setPathComponent(_product->name());
}

WWidget *ProductMenuItem::createItemWidget()
{        
    //<div class="collection" style="background: url(productimages/QEES_Dimmer_billed_tekst_01_thumb.jpg) no-repeat;">
    WContainerWidget *result = new WContainerWidget();
    WContainerWidget *collection = new WContainerWidget(result);
    collection->mouseWentOver().connect(SLOT(this, ProductMenuItem::_mouseWentOver));
    collection->mouseWentOut().connect(SLOT(this, ProductMenuItem::_mouseWentOut));

    collection->setStyleClass("collection");
    collection->decorationStyle().setBackgroundImage(text().toUTF8());

    _faderInvisible = new WContainerWidget(collection);
    _faderInvisible->setStyleClass("fader invisible");

    WContainerWidget *faderInvisible2 = new WContainerWidget(_faderInvisible);
    Wt:WString description(
        "<span class=\"heading\">QEES Dimmer</span>"
        "<span class=\"price\">65 EUR</span>"
        "<span class=\"desc\">QEES Dimmer er en 400 Watt universal lysdmper, med indbygget elmler. Med QEES Dimmer kan du dæmpe lyset, ge hyggen og spare p energien.</span>"
        "<!-- <span class=\"price_sale\"><span>&pound;69.00</span></span> -->", UTF8);

    new WAnchor("#", description, faderInvisible2);

    // <!--<div class="sale_label"></div>-->
    WContainerWidget *salesLabel = new WContainerWidget(collection);
    salesLabel->setStyleClass("sale_label");

    // <!--<div class="sale_label"></div>-->
    WContainerWidget *offerLabel = new WContainerWidget(collection);
    offerLabel->setStyleClass("offer_label");

    //<a href="?productId=3" title="QEES Dimmer" class="fader_link invisible"></a>
    WAnchor * linkis = new WAnchor("#", "",faderInvisible2);
    linkis->setStyleClass("invisible");

  return result;
}

void ProductMenuItem::updateItemWidget(WWidget *itemWidget)
{
    //WMenuItem::updateItemWidget(itemWidget);
    /*
  WAnchor *a = dynamic_cast<WAnchor *>(itemWidget);

  if (a) {
    a->setText(text());

    std::string url;
    if (menu_->internalPathEnabled())
      url = wApp->bookmarkUrl(menu_->internalBasePath() + pathComponent());
    else
      url = "#";

    a->setRef(url);
    a->clicked().setPreventDefault(true);
  }*/
}

void ProductMenuItem::_mouseWentOver()
{
    _faderInvisible->setStyleClass("fader");
}

void ProductMenuItem::_mouseWentOut()
{
    _faderInvisible->setStyleClass("fader invisible");
}
