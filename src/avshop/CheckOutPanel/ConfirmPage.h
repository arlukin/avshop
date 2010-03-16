#ifndef ConfirmPage_H
#define ConfirmPage_H

#include "Wt/WGroupBox"
#include "Wt/WPanel"
#include "Wt/WTable"
#include "Wt/WLineEdit"
#include "Wt/WTextArea"
#include "Wt/WPushButton"
#include "Wt/WString"
using namespace Wt;

class ConfirmPage : public WPanel
{
public:
    ConfirmPage();

    void refresh();
private:    
    void _createCartGroup(WContainerWidget * container_);
    void _createUserGroup(WContainerWidget * container_);
    void _createPaymentGroup(WContainerWidget * container_);
    void _createConfirmGroup(WContainerWidget * container_);
    void _createButtonContainer(WContainerWidget * container_);

    WLineEdit * createLineEdit(WString label_, Wt::WContainerWidget *group_);
    void _onPrev();
    void _onComplete();
};

#endif // ConfirmPage_H
