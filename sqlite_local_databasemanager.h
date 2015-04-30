#ifndef SQLITE_LOCAL_DATABASEMANAGER_H
#define SQLITE_LOCAL_DATABASEMANAGER_H

#include <QWidget>
#include "showwidgets.h"
#include "csqlite_local_db.h"
#include "thread_databasemanager.h"

#define WINDEX_DB_MANAGER 0
#define WINDEX_LOADING 1
#define CBINDEX_DB_LAST_SAVE 0
#define CBINDEX_DB_DEFAULT_EMPTY 1
#define CBINDEX_DB_DEFAULT_TEST 2

namespace Ui {
class SQLite_Local_DatabaseManager;
}

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
        void Start_DB_Manager();
        void SaveDB();
        void terminatedThread(bool Result);
        void SetStatusLoading(QString Msg,int StatValue);

    signals:
        void startThread(int Opt);

    private:
        Ui::SQLite_Local_DatabaseManager *ui;
        ShowWidgets *m_ShowWidgets;
        Thread_Databasemanager *Thread_Database_Manager;
        //BD Local
           CSQLite_Local_DB *m_BD;
        int m_Page_DB_Manager;
        int m_Page_Loading;
};

#endif // SQLITE_LOCAL_DATABASEMANAGER_H
