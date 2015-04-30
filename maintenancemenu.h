#ifndef MAINTENANCEMENU_H
#define MAINTENANCEMENU_H

#include <QWidget>
#include "showwidgets.h"

namespace Ui {
class MaintenanceMenu;
}

class MaintenanceMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MaintenanceMenu(QWidget *parent = 0);
    void SetShowWidgets(ShowWidgets *TShowWidgets){m_ShowWidgets = TShowWidgets;}

    ~MaintenanceMenu();

public slots:
    void ReturnHome();
    void GotoSQLite_Local_DatabaseManager();

private:
    Ui::MaintenanceMenu *ui;
    ShowWidgets *m_ShowWidgets;
};

#endif // MAINTENANCEMENU_H
