#include "sqlite_local_databasemanager.h"
#include "ui_sqlite_local_databasemanager.h"
#include "DataStructures.h"

#include <QDebug>
#include <QThread>

SQLite_Local_DatabaseManager::SQLite_Local_DatabaseManager(QWidget *parent, CSQLite_Local_DB *BD) :
    QWidget(parent),
    ui(new Ui::SQLite_Local_DatabaseManager)
{
    ui->setupUi(this);
    if(BD != NULL)
    {
        m_BD = BD;
        Thread_Database_Manager = new Thread_Databasemanager(BD);
        m_Page_DB_Manager = WINDEX_DB_MANAGER;
        m_Page_Loading = WINDEX_LOADING;

        QObject::connect(ui->B_Home,SIGNAL(clicked()),this,SLOT(ReturnHome()));
        QObject::connect(ui->B_CreateDB_Save,SIGNAL(clicked()),this,SLOT(SaveDB()));
        QObject::connect(ui->B_CB_CreateDB_Valid,SIGNAL(clicked()),this,SLOT(Start_DB_Manager()));
        QObject::connect(m_BD,SIGNAL(SQL_Database_Manager_Status(QString,int)),this,SLOT(SetStatusLoading(QString,int)));
    }
    else
        qDebug() << "[FATAL ERROR] : Uninitiatized SQLite_Local_DatabaseManager (BD = NULL)";
}

void SQLite_Local_DatabaseManager::DB_Manager(int Opt)
{
    switch(Opt)
    {
        case CBINDEX_DB_LAST_SAVE:
        {
            //m_BD->SQL_Database_Manager(EMPTY_DATABASE);
            Thread_Database_Manager->startThread(EMPTY_DATABASE);
            ui->DB_Manager_stackedWidget->setCurrentIndex(WINDEX_LOADING);
            qDebug()<< "-----------DB_Manager : EMPTY_DATABASE";
            break;
        }
        case CBINDEX_DB_DEFAULT_EMPTY:
        {
            //m_BD->SQL_Database_Manager(DEFAULT_DATABASE);
            Thread_Database_Manager->startThread(DEFAULT_DATABASE);
            ui->DB_Manager_stackedWidget->setCurrentIndex(WINDEX_LOADING);
            qDebug()<< "-----------DB_Manager : DEFAULT_DATABASE";
            break;
        }
        case CBINDEX_DB_DEFAULT_TEST:
        {
            //m_BD->SQL_Database_Manager(LOAD_SAVE_DATABASE);
            Thread_Database_Manager->startThread(LOAD_SAVE_DATABASE);
            ui->DB_Manager_stackedWidget->setCurrentIndex(WINDEX_LOADING);
            qDebug()<< "-----------DB_Manager : LOAD_SAVE_DATABASE";
            break;
        }
    }
}

SQLite_Local_DatabaseManager::~SQLite_Local_DatabaseManager()
{
    delete ui;
}

void SQLite_Local_DatabaseManager::ReturnHome()
{
    m_ShowWidgets->ShowWConsoleWindows();
}

void SQLite_Local_DatabaseManager::Start_DB_Manager()
{
    DB_Manager(ui->CB_DB_Create->currentIndex());
}

void SQLite_Local_DatabaseManager::SaveDB()
{
    m_BD->SQL_Database_Manager(SAVE_DATABASE);
    qDebug()<< "-----------DB_Manager : SAVE_DATABASE";

}

void SQLite_Local_DatabaseManager::terminatedThread(bool Result)
{
    if(Result)
        qDebug()<< "[SUCCESS] : Database manager operation";
    else
        qDebug()<< "[ERROR] : Database manager operation";

    ui->DB_Manager_stackedWidget->setCurrentIndex(WINDEX_DB_MANAGER);
}

void SQLite_Local_DatabaseManager::SetStatusLoading(QString Msg, int StatValue)
{
    if( (ui->progressBar->value() == 100) || (StatValue > 100) )
    {
        //QThread::sleep(300);
        ui->Label_ProgressBar->setText("");
        ui->progressBar->setValue(0);
    }
    else
    {
        ui->progressBar->setValue(StatValue);
        ui->Label_ProgressBar->setText(Msg);
    }
}
