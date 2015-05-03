#ifndef THREAD_LOCALDATABASE_AUTOSAVE_H
#define THREAD_LOCALDATABASE_AUTOSAVE_H

#include <QObject>
#include <QThread>

#include "sqlite_local_databasemanager.h"
#include "csqlite_local_db.h"

class SQLite_Local_DatabaseManager;

class Thread_LocalDatabase_AutoSave : public QThread
{
    Q_OBJECT

    private:
        CSQLite_Local_DB *m_BD;
        SQLite_Local_DatabaseManager *m_DatabaseManager;

    public:
        explicit Thread_LocalDatabase_AutoSave(SQLite_Local_DatabaseManager *parent = 0, CSQLite_Local_DB *BD = NULL);
        void run();
        ~Thread_LocalDatabase_AutoSave();

    signals:
        void TerminedThread_LocalDatabase_AutoSave(bool ThreadExitValue);

    public slots:
        void StartThread_LocalDatabase_AutoSave();
};

#endif // THREAD_LOCALDATABASE_AUTOSAVE_H
