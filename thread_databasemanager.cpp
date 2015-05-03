#include "thread_databasemanager.h"
#include <QDebug>

Thread_Databasemanager::Thread_Databasemanager(SQLite_Local_DatabaseManager *DatabaseManager, CSQLite_Local_DB *DB, bool TWithSlowProcess):QThread()
{
    if( (DB != NULL) || (DatabaseManager != NULL) )
    {
        m_DB = DB;
        m_WithSlowProcess = TWithSlowProcess;
        m_DatabaseManager = DatabaseManager;

        if(m_WithSlowProcess == true)
        {
            //connect(m_DB,SIGNAL(SlowProcess(int)), this,SLOT(SlowThread(int)));
            connect(m_DatabaseManager,SIGNAL(startThreadManager(int)), this,SLOT(startThreadManager(int)));
            qDebug() << "Thread_Databasemanager : m_WithSlowProcess = " << m_WithSlowProcess;
        }
        else
        {
            qDebug() << "Thread_Databasemanager : m_WithSlowProcess = " << m_WithSlowProcess;
            connect(m_DatabaseManager,SIGNAL(startThreadAutoSave()), this,SLOT(startThreadAutoSave()));
        }
    }
    else
    {
        qDebug() << "[FATAL ERROR] : Uninitiatized pointer (NULL)";
    }

}

Thread_Databasemanager::~Thread_Databasemanager()
{
    qDebug()<< "End thread : Thread_DatabaseManager";
}

void Thread_Databasemanager::run()
{
    bool Result = false;

    Result = m_DB->SQL_Database_Manager(m_SelectedOption);
    emit terminatedThread(false);

    if(Result)
        exit(0);
    else
        exit(-1);

}

void Thread_Databasemanager::SlowThread(int Timems)
{
   if(isRunning())
   {
     msleep(Timems);
   }
}

void Thread_Databasemanager::startThreadManager(int opt)
{
    m_SelectedOption = opt;
    start();
}

void Thread_Databasemanager::startThreadAutoSave()
{
    m_SelectedOption = SAVE_DATABASE;
    start();
}
