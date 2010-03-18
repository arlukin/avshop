#include "Wt/WString"
#include "ArticleWidget.h"

ArticleWidget::ArticleWidget(std::string translationKey_)
    : WText::WText(WString(WString::tr(translationKey_).toUTF8(), UTF8))
{
    setStyleClass("article");
}
