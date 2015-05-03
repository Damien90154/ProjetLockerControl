#include "thread_localdatabase_autosave.h"

#include <QDebug>

Thread_LocalDatabase_AutoSave::Thread_LocalDatabase_AutoSave(SQLite_Local_DatabaseManager *parent, CSQLite_Local_DB *BD) : QThread()
{
    if( (BD != NULL) || (parent != NULL) )
    {
        m_BD = BD;
        m_DatabaseManager = parent;

        connect(m_DatabaseManager, SIGNAL(startThreadAutoSave()), this, SLOT(StartThread_LocalDatabase_AutoSave()));
    }
    else
        qDebug()<< "[FATAL ERROR] : Uninitialized pointer (NULL)";
}

void Thread_LocalDatabase_AutoSave::run()
{
    bool Result = false;

    Result = m_BD->DataBase_AutoSave_Needed();
    emit TerminedThread_LocalDatabase_AutoSave(Result);

    if(Result)
        exit(0);
    else
        exit(-1);
}

Thread_LocalDatabase_AutoSave::~Thread_LocalDatabase_AutoSave()
{

}

void Thread_LocalDatabase_AutoSave::StartThread_LocalDatabase_AutoSave()
{
    start();
}

