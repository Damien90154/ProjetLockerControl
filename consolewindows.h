#ifndef CONSOLEWINDOWS_H
#define CONSOLEWINDOWS_H

#include <QMainWindow>
#include <QTimer>
#include <QMouseEvent>
#include <QList>
#include "country.h"
#include "customer.h"
#include "login.h"
#include "menudelivery.h"
#include "deliveryconfirm.h"
#include "scanpackage.h"
#include "openemptybox.h"
#include "boxchoice.h"
#include "deliveryconfirm.h"
#include "setting.h"
#include "settingsystem.h"
#include "showwidgets.h"
#include "showpackagebox.h"
#include "stowpackages.h"
#include "clms_db.h"
#include "csqlite_local_db.h"
#include "maintenancemenu.h"
#include "sqlite_local_databasemanager.h"
#include "doorsmanager.h"

class ConsoleWindows;

namespace Ui {
class ConsoleWindows;
}

class ConsoleWindows : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConsoleWindows(QWidget *parent = 0);

    void Initialization_Widgets();
    void Init_Show_Widgets();

    void mousePressEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);

    //evenement change pays
    void changeEvent(QEvent *e);


    ~ConsoleWindows();


public slots:

    void Show_WCustomer();
    void Show_WConsole();
    void Show_Login();
    void SelectPays(int);

signals:
    void refresh();

private slots:
    void HideB_DeliveryMaintenance();

private:

    Ui::ConsoleWindows *ui;


 //positions Widgets
    int m_position_WLogin;
    int m_position_WSetting;
    int m_position_WSettingSystem;
    int m_position_WCustomer;
    int m_position_WConsole;
    int m_position_WMenuDelivery;
    int m_position_WEmptyBox;
    int m_position_WBoxChoice;
    int m_position_WScanPackage;
    int m_position_WDeliveryComfirm;
    int m_position_WShowPackageBox;
    int m_position_WStowPackages;
    int m_position_WMaintenanceMenu;
    int m_position_WSQLite_Local_DatabaseManager;
    int m_position_WDoorsManager;

    ShowWidgets m_WidgetsShow;

 //Customer
    Customer *m_Widget_Customer;

 //Livraison
    MenuDelivery *m_Widget_MenuDelivery;
    OpenEmptyBox *m_Widget_EmptyBox;
    BoxChoice *m_Widget_BoxChoice;
    ScanPackage *m_Widget_ScanPackage;
    DeliveryConfirm *m_Widget_DeliveryComfirm;
    ShowPackageBox *m_Widget_ShowPackageBox;
    StowPackages *m_Widget_StowPackages;

 //Configuration systeme
    Setting *m_Widget_Setting;
    SettingSystem *m_Widget_SettingSystem;

 //Maintenance
    MaintenanceMenu *m_Widget_MaintenanceMenu;
    SQLite_Local_DatabaseManager *m_Widget_SQLite_Local_DatabaseManager;
    DoorsManager *m_Widget_DoorsManager;

 //Login
    Login *m_Widget_Login;

 //BD Local
    CSQLite_Local_DB *m_BD;

 //CDoors
    CDoors *m_Doors;

    //Serveur LMS
    CLMS_DB *m_LMS;

 //Timer pour temps écoulée si pas d'action
    QTimer *m_timer;
    QList<QIcon> m_flags;
    QStringList m_pays;
    int m_compteur;

 //Traduction
    Country *m_country;



};

#endif // CONSOLEWINDOWS_H
