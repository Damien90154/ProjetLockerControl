#include "consolewindows.h"
#include "ui_consolewindows.h"
#include <QStringList>
#include <QPropertyAnimation>
#include <qdebug.h>

ConsoleWindows::ConsoleWindows(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConsoleWindows)
{
    ui->setupUi(this);
    //eleve les bordures
    //setWindowFlags(Qt::FramelessWindowHint);
     m_compteur = 0;

    //serveur LMS
    m_LMS = new CLMS_DB();

    //création de la base de donnée
    m_BD = new CSQLite_Local_DB(m_LMS);
    if(m_BD->Get_DataBaseIsReady())
    {
        m_BD->SQL_Database_Manager(DEFAULT_DATABASE);
    }
    else{

        close();
    }

    //CDoors
    m_Doors = new CDoors(m_BD);


    //initialisation des Widgets
    Initialization_Widgets();

    //partage des postions Widgets et du stackedwidget pour les autres classes
    Init_Show_Widgets();

    //Creation timer
    m_timer = new QTimer(this);

    //test list pays
    m_pays <<"France"<<"English"<<QString("Español")<<"Deutsch";

    ui->comboBox->addItems(m_pays);

    m_flags<<QIcon(":/flags/France")<<QIcon(":/flags/English")<<QIcon(":/flags/Spain")<<QIcon(":/flags/German");
    for(int i = 0 ; i<m_flags.count();i++){

        ui->comboBox->setItemIcon(i,m_flags[i]);
    }

   //translator
    m_country = new Country();

   //connection bouton
    connect(ui->B_TakePackage,SIGNAL(clicked()),this,SLOT(Show_WCustomer()));
    connect(ui->B_DeliveryAndMaintenace,SIGNAL(clicked()),this,SLOT(Show_Login()));
    connect(m_timer,SIGNAL(timeout()),this,SLOT(HideB_DeliveryMaintenance()));
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(SelectPays(int)));
    ui->B_DeliveryAndMaintenace->setVisible(false);

    //gestion des evenements des widgets
    ui->B_DeliveryAndMaintenace->installEventFilter(this);
    ui->P_Home->installEventFilter(this);

}

ConsoleWindows::~ConsoleWindows()
{

    delete ui;
}

void ConsoleWindows::Initialization_Widgets()
{
    m_position_WConsole = ui->stackedWidget->currentIndex();

  //Partie Client
   //Widget Customer
    m_Widget_Customer = new Customer(m_BD);
    m_position_WCustomer = ui->stackedWidget->addWidget(m_Widget_Customer);

   //Widget ShowPackageBox
    m_Widget_ShowPackageBox = new ShowPackageBox(m_Widget_Customer,m_BD,m_Doors);
    m_position_WShowPackageBox = ui->stackedWidget->addWidget(m_Widget_ShowPackageBox);

    //Widget Login
     m_Widget_Login = new Login(m_BD);
     m_position_WLogin = ui->stackedWidget->addWidget(m_Widget_Login);

  //Partie Livraison
    //Widget MenuDelivery
    m_Widget_MenuDelivery = new MenuDelivery();
    m_position_WMenuDelivery = ui->stackedWidget->addWidget(m_Widget_MenuDelivery);

   //Widget Consignes Vides
    m_Widget_EmptyBox = new OpenEmptyBox(m_BD,m_Widget_MenuDelivery,m_Doors);
    m_position_WEmptyBox = ui->stackedWidget->addWidget(m_Widget_EmptyBox);

   //Widget selection consigne
    m_Widget_BoxChoice = new BoxChoice(m_Widget_MenuDelivery,m_BD);
    m_position_WBoxChoice = ui->stackedWidget->addWidget(m_Widget_BoxChoice);

   //Widget pour saisir les n°colis
    m_Widget_ScanPackage = new ScanPackage(m_Widget_BoxChoice);
    m_position_WScanPackage = ui->stackedWidget->addWidget(m_Widget_ScanPackage);

   //Widget stowpackages
    m_Widget_StowPackages = new StowPackages(m_Widget_ScanPackage,m_Widget_BoxChoice,m_BD,m_Doors);
    m_position_WStowPackages = ui->stackedWidget->addWidget(m_Widget_StowPackages);

   //Widget confirmation de la livraison
    m_Widget_DeliveryComfirm = new DeliveryConfirm(m_BD,m_LMS,m_Widget_StowPackages,m_Widget_BoxChoice);
    m_position_WDeliveryComfirm = ui->stackedWidget->addWidget(m_Widget_DeliveryComfirm);

  //Partie Systeme Maintenance
   //Widget Setting
    m_Widget_Setting = new Setting();
    m_position_WSetting = ui->stackedWidget->addWidget(m_Widget_Setting);

   //Widget SettingSystem
    m_Widget_SettingSystem = new SettingSystem();
    m_position_WSettingSystem = ui->stackedWidget->addWidget(m_Widget_SettingSystem);

   //Widget MaintenanceMenu
    m_Widget_MaintenanceMenu = new MaintenanceMenu();
    m_position_WMaintenanceMenu = ui->stackedWidget->addWidget(m_Widget_MaintenanceMenu);

   //Widget SQLite_Local_DatabaseManager
    m_Widget_SQLite_Local_DatabaseManager = new SQLite_Local_DatabaseManager(m_Widget_Setting,m_BD);
    m_position_WSQLite_Local_DatabaseManager = ui->stackedWidget->addWidget(m_Widget_SQLite_Local_DatabaseManager);

   //Widget DoorsManager
    m_Widget_DoorsManager = new DoorsManager(m_Widget_Setting,m_BD,m_Doors ,m_Widget_BoxChoice);
    m_position_WDoorsManager = ui->stackedWidget->addWidget(m_Widget_DoorsManager);

}
void ConsoleWindows::Init_Show_Widgets()
{

    //partage positions widget entre widgets
    m_WidgetsShow.SetPosBoxChoice(m_position_WBoxChoice);
    m_WidgetsShow.SetPosConsoleWindows(m_position_WConsole);
    m_WidgetsShow.SetPosCustomer(m_position_WCustomer);
    m_WidgetsShow.SetPosDeliveryConfirm(m_position_WDeliveryComfirm);
    m_WidgetsShow.SetPosLogin(m_position_WLogin);
    m_WidgetsShow.SetPosMenuDelivery(m_position_WMenuDelivery);
    m_WidgetsShow.SetPosOpenEmptyBox(m_position_WEmptyBox);
    m_WidgetsShow.SetPosScanPackage(m_position_WScanPackage);
    m_WidgetsShow.SetPosSetting(m_position_WSetting);
    m_WidgetsShow.SetPosShowPackageBox(m_position_WShowPackageBox);
    m_WidgetsShow.SetPosStowPackages(m_position_WStowPackages);
    m_WidgetsShow.SetStackedWidget(ui->stackedWidget);
    m_WidgetsShow.SetPosMaintenanceMenu(m_position_WMaintenanceMenu);
    m_WidgetsShow.SetPosSQLite_Local_DatabaseManager(m_position_WSQLite_Local_DatabaseManager);
    m_WidgetsShow.SetPosSettingSystem(m_position_WSettingSystem);

    //Widget Customer
    m_Widget_Customer->SetShowWidgets(&m_WidgetsShow);
    m_Widget_ShowPackageBox->SetShowWidgets(&m_WidgetsShow);


   //Widget MenuDelivery
    m_Widget_MenuDelivery->SetShowWidgets(&m_WidgetsShow);


   //Widget Consignes Vides
    m_Widget_EmptyBox->SetShowWidgets(&m_WidgetsShow);


   //Widget selection consigne
    m_Widget_BoxChoice->SetShowWidgets(&m_WidgetsShow);


   //Widget pour saisir les n°colis
    m_Widget_ScanPackage->SetShowWidgets(&m_WidgetsShow);

    m_Widget_StowPackages->SetShowWidgets(&m_WidgetsShow);

   //Widget confirmation de la livraison
    m_Widget_DeliveryComfirm->SetShowWidgets(&m_WidgetsShow);


   //Widget Login
    m_Widget_Login->SetShowWidgets(&m_WidgetsShow);


   //Widget Setting
    m_Widget_Setting->SetShowWidgets(&m_WidgetsShow);
    m_Widget_SettingSystem->SetShowWidgets(&m_WidgetsShow);

   //Widget Maintenance
    m_Widget_MaintenanceMenu->SetShowWidgets(&m_WidgetsShow);
    m_Widget_SQLite_Local_DatabaseManager->SetShowWidgets(&m_WidgetsShow);
    m_Widget_DoorsManager->SetShowWidgets(&m_WidgetsShow);


}

//affiche ihm Customer
void ConsoleWindows::Show_WCustomer()
{
    //cache bouton livraison
    HideB_DeliveryMaintenance();

   QPropertyAnimation *fondu ;
    QRect pGeo(m_Widget_Customer->x(),m_Widget_Customer->y(),m_Widget_Customer->width(),m_Widget_Customer->height());

    fondu = new QPropertyAnimation(m_Widget_Customer,"geometry");
    fondu->setEasingCurve(QEasingCurve::InOutSine);
    fondu->setDuration(500);
    fondu->setStartValue(QRect(m_Widget_Customer->x()-1500,pGeo.y(),pGeo.width(),pGeo.height()));
    fondu->setEndValue(pGeo);
    fondu->start();

    ui->stackedWidget->setCurrentIndex(m_position_WCustomer);
}

//affiche ihm principal
void ConsoleWindows::Show_WConsole()
{
    ui->stackedWidget->setCurrentIndex(m_position_WConsole);
}

void ConsoleWindows::Show_Login()
{
    HideB_DeliveryMaintenance();

    m_Widget_Login->Refresh();
    m_WidgetsShow.ShowWLogin();
}

void ConsoleWindows::mousePressEvent(QMouseEvent *mouse)
{

    if(mouse->buttons() == Qt::LeftButton)
    {
        //m_timer->stop();

    }
    else{

       // m_timer->start(7000);
    }
}


bool ConsoleWindows::eventFilter(QObject *obj, QEvent *event)
{
    bool result = false;

    if(obj == ui->P_Home && event->type()==QEvent::MouseButtonPress)
    {
        m_compteur++;
        if(m_compteur == 3)
        {
            ui->B_DeliveryAndMaintenace->setVisible(true);
            ui->spacedelivrery->changeSize(40,20,QSizePolicy::Fixed,QSizePolicy::Fixed);
            adjustSize();

        }
        result=true;
    }

    if(obj == ui->B_DeliveryAndMaintenace && event->type()==QEvent::Show)
    {
        m_timer->start(20000);
        result = true;
    }

    if(obj == ui->B_DeliveryAndMaintenace && event->type()==QEvent::Hide)
    {
        m_timer->stop();
        result = true;
    }

    return result;
}

void ConsoleWindows::HideB_DeliveryMaintenance()
{
    m_compteur = 0;
    ui->B_DeliveryAndMaintenace->setVisible(false);
    ui->spacedelivrery->changeSize(0,0,QSizePolicy::Fixed,QSizePolicy::Fixed);
}

void ConsoleWindows::SelectPays(int flags)
{

    QEvent *e = new QEvent(QEvent::LanguageChange);

    switch (flags) {
    case 0://select french
             m_country->SetFrench();
             changeEvent(e);
             break;

    case 1://select english
            m_country->SetEnglish();
            changeEvent(e);
            break;

    case 2://select spanish
            m_country->SetEspanol();
            changeEvent(e);
            break;

    case 3://select german
            m_country->SetDeutsch();
            changeEvent(e);
            break;
    default:
        break;
    }
    delete e;
}

void ConsoleWindows::changeEvent(QEvent *e)
{
    if(e->type() == QEvent::LanguageChange )
    {
        ui->retranslateUi(this);
        m_Widget_BoxChoice->retranslateUi();
        m_Widget_Customer->retranslateUi();
        m_Widget_DeliveryComfirm->retranslateUi();
        m_Widget_EmptyBox->retranslateUi();
        m_Widget_Login->retranslateUi();
        m_Widget_MenuDelivery->retranslateUi();
        m_Widget_ScanPackage->retranslateUi();
        m_Widget_Setting->retranslateUi();
        m_Widget_ShowPackageBox->retranslateUi();
        m_Widget_StowPackages->retranslateUi();

    }
}


