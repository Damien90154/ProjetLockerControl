#include "maintenancemenu.h"
#include "ui_maintenancemenu.h"

MaintenanceMenu::MaintenanceMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MaintenanceMenu)
{
    ui->setupUi(this);
    QObject::connect(ui->B_Home,SIGNAL(clicked()),this,SLOT(ReturnHome()));
    QObject::connect(ui->B_SiteConfig,SIGNAL(clicked()),this,SLOT(ReturnHome()));
    QObject::connect(ui->B_DoorsManager,SIGNAL(clicked()),this,SLOT(ReturnHome()));
    QObject::connect(ui->B_Restarts,SIGNAL(clicked()),this,SLOT(ReturnHome()));
    QObject::connect(ui->B_DatabaseManager,SIGNAL(clicked()),this,SLOT(GotoSQLite_Local_DatabaseManager()));
}

MaintenanceMenu::~MaintenanceMenu()
{
    delete ui;
}

void MaintenanceMenu::ReturnHome()
{
    m_ShowWidgets->ShowWConsoleWindows();
}

void MaintenanceMenu::GotoSQLite_Local_DatabaseManager()
{
    m_ShowWidgets->ShowWSQLite_Local_DatabaseManager();
}
