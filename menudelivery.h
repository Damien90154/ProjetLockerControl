#ifndef MENUDELIVERY_H
#define MENUDELIVERY_H

#include <QWidget>

#include "showwidgets.h"

namespace Ui {
class MenuDelivery;
}

class MenuDelivery : public QWidget
{
    Q_OBJECT

public:
    explicit MenuDelivery(QWidget *parent = 0);
    void SetShowWidgets(ShowWidgets *TShowWidgets){m_ShowWidgets = TShowWidgets;}


    ~MenuDelivery();

    void retranslateUi();
public slots:
    void Deposit();
    void OpenBoxEmpty();
    void ReturnHome();

signals:
    void refreshGraphicsBox();
    void showDoors();

private:
    Ui::MenuDelivery *ui;
    ShowWidgets *m_ShowWidgets;

};

#endif // MENUDELIVERY_H
