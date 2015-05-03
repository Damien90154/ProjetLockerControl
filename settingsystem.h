#ifndef SETTINGSYSTEM_H
#define SETTINGSYSTEM_H

#include <QWidget>
#include "showwidgets.h"
#include "customxml.h"

namespace Ui {
class SettingSystem;
}

class SettingSystem : public QWidget
{
    Q_OBJECT

public:
    explicit SettingSystem(QWidget *parent = 0);
    void SetShowWidgets(ShowWidgets *TShowWidgets){m_ShowWidgets = TShowWidgets;}
    ~SettingSystem();

private slots:
    void on_B_Cancel_clicked();

private:
    Ui::SettingSystem *ui;
    ShowWidgets *m_ShowWidgets;
    CustomXml *m_Xml;
};

#endif // SETTINGSYSTEM_H
