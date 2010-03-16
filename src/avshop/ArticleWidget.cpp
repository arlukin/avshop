#include "ArticleWidget.h"

ArticleWidget::ArticleWidget(std::string translationKey_)
    : WText::WText(WString::tr(translationKey_))
{
    setStyleClass("article");
}
