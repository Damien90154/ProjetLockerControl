#ifndef THREAD_DATABASEMANAGER_H
#define THREAD_DATABASEMANAGER_H

#include <QThread>
#include "csqlite_local_db.h"
#include "DataStructures.h"

class Thread_Databasemanager;

class Thread_Databasemanager :  public QThread
{
    Q_OBJECT

    public:
        Thread_Databasemanager(CSQLite_Local_DB *DB=NULL);
        ~Thread_Databasemanager();
        void run();

    private:
        int m_SelectedOption;
        QString m_LoadMessage;
        int m_LoadValue;
        CSQLite_Local_DB *m_DB;

    signals:
        void terminatedThread(bool);

    public slots:
        void startThread(int opt);
};

#endif // THREAD_DATABASEMANAGER_H
