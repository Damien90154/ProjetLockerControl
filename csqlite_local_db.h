#ifndef CSQLITE_LOCAL_DB_H
#define CSQLITE_LOCAL_DB_H

#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QObject>

#include "DataStructures.h"
#include "clms_db.h"


class CSQLite_Local_DB : public QObject
{
    Q_OBJECT

    private:
        CLMS_DB *m_LMS_Server;
        QSqlDatabase m_DataBase;
        QString m_DatabaseName;
        QString m_SQL_File_DatabaseEmpty_Path;
        QString m_SQL_File_DatabaseDefault_Path;
        QString m_SQL_File_DatabaseLastSave_Path;
        QString m_SQL_File_DatabaseLastSave_Path_FromLMS;
        QList<QString> m_Infos_Database;
        bool m_DataBaseIsReady;

    protected:
        QList<QString> ReadSQL_File(QString FilePath);
        bool WriteSQL_File(QString FilePath,QString Data);
        bool SaveDatabase(QString FilePath);
        bool LoadDatabaseSave(QString FilePath);
        bool Connect_DB();
        bool Delete_DB();
        QString Get_SiteName();

    public:
        explicit CSQLite_Local_DB(CLMS_DB *LMS_Server = NULL);
        ~CSQLite_Local_DB();

        QList<QString> DataBaseStatus();
        bool Get_DataBaseIsReady(){return this->m_DataBaseIsReady;}
        QString lastError();
        QSqlQuery SendQuery(QString Query);
        QList<struct_DoorsStatus> SendQueryDoorsStatus(QString Query);
        int Login(QString);
        bool SavePerfomAction(QString Table,QString Action);
        int CheckExtractCode(QString ExtractCode);
        bool DeleteExtractCode(QString UsedExtractCode);
        QList<int> GetBoxesListConsumer(QString ExtractCode);
        QList<struct struct_DoorGeom> GetBoxesList();
        bool UpdateLocalData(QList<struct struct_PackagesUseBox> UpdatedPackagesUseBoxList);
        bool SQL_Database_Manager(int Option);
        QList<int> GetFreeBoxes();
        bool SendQueryDoorsIsClosed(QString Query);
        bool SetDammagedBoxes(QList<int> DammagedBoxes);
        bool UnsetDammagedBoxes(QList<int> FixedBoxes);
        QList<int> GetDammagedBoxes();
        bool DataBase_AutoSave_Needed();

    signals:
        void CurrentProcessLoading(QString,int);
        void SlowProcess(int);

};

#endif // CSQLITE_LOCAL_DB_H
