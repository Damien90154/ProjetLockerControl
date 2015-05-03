#include <QDebug>
#include <QThread>

#include "sqlite_local_databasemanager.h"
#include "ui_sqlite_local_databasemanager.h"
#include "DataStructures.h"


SQLite_Local_DatabaseManager::SQLite_Local_DatabaseManager(QWidget *parent, CSQLite_Local_DB *BD) :
    QWidget(parent),
    ui(new Ui::SQLite_Local_DatabaseManager)
{
    ui->setupUi(this);
    if(BD != NULL)
    {
        m_BD = BD;
        m_Thread_Database_Manager = new Thread_Databasemanager(this,m_BD);
        m_Thread_Database_Manager_AutoSave = new Thread_LocalDatabase_AutoSave(this,m_BD);
        m_Page_DB_Manager = WINDEX_DB_MANAGER;
        m_Page_Loading = WINDEX_LOADING;
        m_AutoSaveInterval_Seconds = AUTOSAVE_DATABASE_TIMEOUT_SECONDS*1000;
        m_EndLoadingTimer = new QTimer();
        m_AutoSave_Database_Timer = new QTimer();

        connect(m_AutoSave_Database_Timer,SIGNAL(timeout()), this, SLOT(TimeOutAutoSave()));
        connect(m_EndLoadingTimer,SIGNAL(timeout()), this,SLOT(TimeOutLoading()),Qt::QueuedConnection);
        connect(ui->B_Home,SIGNAL(clicked()),this,SLOT(ReturnHome()));
        connect(ui->B_CreateDB_Save,SIGNAL(clicked()),this,SLOT(SaveDB()));
        connect(ui->B_CB_CreateDB_Valid,SIGNAL(clicked()),this,SLOT(Start_DB_Manager()));
        connect(ui->B_LoadingValid, SIGNAL(clicked()), this, SLOT(ReturnDB_Manager()));
        connect(m_BD, SIGNAL(CurrentProcessLoading(QString,int)), this,SLOT(SetStatusLoading(QString,int)));
        connect(m_Thread_Database_Manager,SIGNAL(terminatedThread(bool)), this,SLOT(terminatedThreadManager(bool)));
        connect(m_Thread_Database_Manager_AutoSave,SIGNAL(TerminedThread_LocalDatabase_AutoSave(bool)), this, SLOT(terminatedThreadAutoSave(bool)));

        ui->DB_Manager_stackedWidget->setCurrentIndex(WINDEX_DB_MANAGER);
        ui->L_AutoReturnDB_Manager->setText("");
        m_AutoSave_Database_Timer->start(m_AutoSaveInterval_Seconds);
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
            emit startThreadManager(EMPTY_DATABASE);
            ui->DB_Manager_stackedWidget->setCurrentIndex(WINDEX_LOADING);
            qDebug()<< "-----------DB_Manager : EMPTY_DATABASE";
            break;
        }
        case CBINDEX_DB_DEFAULT_EMPTY:
        {
            //m_BD->SQL_Database_Manager(DEFAULT_DATABASE);
            emit startThreadManager(DEFAULT_DATABASE);
            ui->DB_Manager_stackedWidget->setCurrentIndex(WINDEX_LOADING);
            qDebug()<< "-----------DB_Manager : DEFAULT_DATABASE";
            break;
        }
        case CBINDEX_DB_DEFAULT_TEST:
        {
            //m_BD->SQL_Database_Manager(LOAD_SAVE_DATABASE);
            emit startThreadManager(LOAD_SAVE_DATABASE);
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

void SQLite_Local_DatabaseManager::ReturnDB_Manager()
{
    ui->DB_Manager_stackedWidget->setCurrentIndex(WINDEX_DB_MANAGER);
    ui->B_LoadingValid->setEnabled(false);
}

void SQLite_Local_DatabaseManager::Start_DB_Manager()
{
    DB_Manager(ui->CB_DB_Create->currentIndex());
}

void SQLite_Local_DatabaseManager::SaveDB()
{
    ui->DB_Manager_stackedWidget->setCurrentIndex(WINDEX_LOADING);
    emit startThreadManager(SAVE_DATABASE);
    qDebug()<< "-----------DB_Manager : SAVE_DATABASE";
}

void SQLite_Local_DatabaseManager::terminatedThreadManager(bool ThreadExitValue)
{
    if(ThreadExitValue)
        qDebug()<< "[SUCCESS] : Database manager operation";
    else
        qDebug()<< "[ERROR] : Database manager operation";
}

void SQLite_Local_DatabaseManager::SetStatusLoading(QString Message, int Value)
{
    if(ui->DB_Manager_stackedWidget->currentIndex() == WINDEX_LOADING)
    {
        if(Value < 12)
        {
            ui->progressBar->setValue(0);
            ui->Label_ProgressBar->setText(" ");
            ui->B_LoadingValid->setEnabled(true);
            m_EndLoadingTimer->start(1);
        }

        if(Value == 100)
            m_EndLoadingTimer->start(1);

        if(Value > 100)
            ui->B_LoadingValid->setEnabled(true);
        else
        {
            ui->progressBar->setValue(Value);
            ui->Label_ProgressBar->setText(Message);
        }
    }
    else
    {
        m_EndLoadingTimer->stop();
    }
}

void SQLite_Local_DatabaseManager::TimeOutLoading()
{
    static int Cmpt = 0;

    if(ui->DB_Manager_stackedWidget->currentIndex() == WINDEX_LOADING)
    {
        if(Cmpt == END_LOADING_TIMEOUT_SECONDS)
        {
            Cmpt = 0;
            ui->L_AutoReturnDB_Manager->setText("");
            m_EndLoadingTimer->stop();
            ReturnDB_Manager();
        }
        else
        {
            m_EndLoadingTimer->start(1000);
            ui->L_AutoReturnDB_Manager->setText("Retour automatique dans "+ QString::number(END_LOADING_TIMEOUT_SECONDS-Cmpt,10) +" secondes.");
            Cmpt++;
        }
    }
    else
    {
        m_EndLoadingTimer->stop();
        Cmpt = 0;
    }
}

void SQLite_Local_DatabaseManager::TimeOutAutoSave()
{
   if(m_Thread_Database_Manager_AutoSave->wait(2000))
    {
        qDebug() << "---------------------------<[ AUTO SAVE NEEDED ]>----------------------------";
        emit startThreadAutoSave();
        m_AutoSave_Database_Timer->start(m_AutoSaveInterval_Seconds);
   }
   else{

       qDebug() <<"erreur wait";
   }

}

void SQLite_Local_DatabaseManager::terminatedThreadAutoSave(bool ThreadExitValue)
{
    if(ThreadExitValue)
        qDebug()<< "[SUCCESS] : (AutoSave) Database manager operation";
    else
    {
        qDebug()<< "[ERROR] : (AutoSave) Database manager operation try again in 1 minute !";
        m_AutoSave_Database_Timer->stop();
        m_AutoSave_Database_Timer->start(60000);
    }
}
