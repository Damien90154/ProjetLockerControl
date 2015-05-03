#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include "showwidgets.h"

namespace Ui {
class Setting;
}

class Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = 0);
    void SetShowWidgets(ShowWidgets *TShowWidgets){m_ShowWidgets = TShowWidgets;}

    ~Setting();
    void retranslateUi();
public slots:
    void ReturnHome();
    void ShowMaintenanceMenu();

private slots:
    void ShowSettingSystem();
private:
    Ui::Setting *ui;
    ShowWidgets *m_ShowWidgets;
};

#endif // SETTING_H
