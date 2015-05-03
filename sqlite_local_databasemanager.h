#ifndef SQLITE_LOCAL_DATABASEMANAGER_H
#define SQLITE_LOCAL_DATABASEMANAGER_H

#include <QWidget>
#include <QTimer>

#include "showwidgets.h"
#include "csqlite_local_db.h"
#include "thread_databasemanager.h"
#include "thread_localdatabase_autosave.h"

#define WINDEX_DB_MANAGER 0
#define WINDEX_LOADING 1
#define CBINDEX_DB_LAST_SAVE 0
#define CBINDEX_DB_DEFAULT_EMPTY 1
#define CBINDEX_DB_DEFAULT_TEST 2
#define END_LOADING_TIMEOUT_SECONDS 5
#define AUTOSAVE_DATABASE_TIMEOUT_SECONDS 900 //15mns

namespace Ui {
class SQLite_Local_DatabaseManager;
}

class Thread_Databasemanager;
class Thread_LocalDatabase_AutoSave;

class SQLite_Local_DatabaseManager : public QWidget
{
    Q_OBJECT

    public:
        explicit SQLite_Local_DatabaseManager(QWidget *parent = 0,CSQLite_Local_DB *BD = NULL);
        void SetShowWidgets(ShowWidgets *TShowWidgets){m_ShowWidgets = TShowWidgets;}
        void DB_Manager(int Opt);

        ~SQLite_Local_DatabaseManager();

    public slots:
        void ReturnHome();
        void ReturnDB_Manager();
        void Start_DB_Manager();
        void SaveDB();
        void SetStatusLoading(QString Message,int Value);

    signals:
        void startThreadManager(int Opt);
        void startThreadAutoSave();

    private slots:
        void TimeOutLoading();
        void TimeOutAutoSave();
        void terminatedThreadAutoSave(bool ThreadExitValue);
        void terminatedThreadManager(bool ThreadExitValue);

    private:
        Ui::SQLite_Local_DatabaseManager *ui;
        ShowWidgets *m_ShowWidgets;
        Thread_Databasemanager *m_Thread_Database_Manager;
        Thread_LocalDatabase_AutoSave *m_Thread_Database_Manager_AutoSave;
        QTimer *m_EndLoadingTimer;
        QTimer *m_AutoSave_Database_Timer;
        //BD Local
           CSQLite_Local_DB *m_BD;
        int m_Page_DB_Manager;
        int m_Page_Loading;
        int m_AutoSaveInterval_Seconds;
};

#endif // SQLITE_LOCAL_DATABASEMANAGER_H
