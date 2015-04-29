#ifndef CSQLITE_LOCAL_DB_H
#define CSQLITE_LOCAL_DB_H

#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QSqlError>
#include <QFile>
#include "DataStructures.h"

class CSQLite_Local_DB
{
    private:
        QSqlDatabase m_DataBase;
        QString m_DatabaseName;
        QString m_SQL_File_DatabaseEmpty_Path;
        QString m_SQL_File_DatabaseDefault_Path;
        QString m_SQL_File_DatabaseLastSave_Path;
        QList<QString> m_Infos_Database;
        bool m_DataBaseIsReady;

    protected:
        QList<QString> ReadSQL_File(QString FilePath);
        bool WriteSQL_File(QString FilePath,QString Data);
        bool SaveDatabase(QString FilePath);
        bool LoadDatabaseSave(QString FilePath);

    public:
        CSQLite_Local_DB();
        ~CSQLite_Local_DB();

        QList<QString> DataBaseStatus();
        bool Get_DataBaseIsReady(){return this->m_DataBaseIsReady;}
        bool Connect_DB();
        bool Delete_DB();

        QString lastError();
        bool SendQuery(QString Query);
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

};

#endif // CSQLITE_LOCAL_DB_H
