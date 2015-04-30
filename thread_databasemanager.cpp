#include "thread_databasemanager.h"
#include <QDebug>

Thread_Databasemanager::Thread_Databasemanager(CSQLite_Local_DB *DB):QThread()
{
    if(DB != NULL)
    {
        m_DB = DB;
    }
    else
    {
        qDebug() << "[FATAL ERROR] : Uninitiatized SQLite_Local_DatabaseManager (BD = NULL)";
    }
}

Thread_Databasemanager::~Thread_Databasemanager()
{
    qDebug()<< "End thread : Thread_DatabaseManager";
}

void Thread_Databasemanager::run()
{
    bool Result;

    Result = m_DB->SQL_Database_Manager(m_SelectedOption);
    emit terminatedThread(Result);
    exit(0);
}

void Thread_Databasemanager::startThread(int opt)
{
    m_SelectedOption = opt;
    start();
}
