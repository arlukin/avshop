#ifndef ARTICLEWIDGET_H
#define ARTICLEWIDGET_H

#include <string>

#include <Wt/WText>
using namespace Wt;

class ArticleWidget : public WText
{
public:
    ArticleWidget(std::string translationKey_);
};

#endif // ARTICLEWIDGET_H
