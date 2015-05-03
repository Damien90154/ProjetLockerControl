#ifndef THREAD_DATABASEMANAGER_H
#define THREAD_DATABASEMANAGER_H

#include <QThread>

#include "csqlite_local_db.h"
#include "DataStructures.h"
#include "sqlite_local_databasemanager.h"

class Thread_Databasemanager;
class SQLite_Local_DatabaseManager;

class Thread_Databasemanager :  public QThread
{
    Q_OBJECT

    public:
        Thread_Databasemanager(SQLite_Local_DatabaseManager *DatabaseManager = NULL, CSQLite_Local_DB *DB = NULL, bool WithSlowProcess = false);
        ~Thread_Databasemanager();
        void run();

    private:
        int m_SelectedOption;
        bool m_WithSlowProcess;
        CSQLite_Local_DB *m_DB;
        SQLite_Local_DatabaseManager *m_DatabaseManager;

    signals:
        void terminatedThread(bool);

    public slots:
        void SlowThread(int Timems);
        void startThreadManager(int opt);
        void startThreadAutoSave();
};

#endif // THREAD_DATABASEMANAGER_H
