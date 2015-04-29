#include "csqlite_local_db.h"

#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QFile>
#include <QSqlResult>
#include <QSqlRecord>
#include <QDebug>
#include <QDateTime>

CSQLite_Local_DB::CSQLite_Local_DB()
{
    this->m_DatabaseName = "LockerControlDatabase.sqlite";
    this->m_SQL_File_DatabaseEmpty_Path = "LC_SQL_files/LockerControl_SQL_File_DatabaseEmpty.sql";
    this->m_SQL_File_DatabaseDefault_Path = "LC_SQL_files/LockerControl_SQL_File_DatabaseDefault.sql";
    this->m_SQL_File_DatabaseLastSave_Path = "LC_SQL_files/LockerControl_SQL_File_DatabaseLastSave.sql";

    if(Connect_DB())
    {
        this->m_DataBaseIsReady = true;  // Open database : Open
    }
    else
    {
        this->m_DataBaseIsReady = false; // Open database : Fail
    }
}

CSQLite_Local_DB::~CSQLite_Local_DB()
{
    // Close database
    this->m_DataBase.close();
}

QList<QString> CSQLite_Local_DB::DataBaseStatus()
{
    QList<QString> TablesList = this->m_DataBase.tables();
    this->m_Infos_Database << "--------------------------------< DATABASE INFOS >--------------------------------"
                           << "Driver : " + this->m_DataBase.driverName()
                           << "Database name : " + this->m_DataBase.databaseName()
                           << "Connection name : " + this->m_DataBase.connectionName()
                           << "Connect options : " + this->m_DataBase.connectOptions()
                           << "Host : " + this->m_DataBase.hostName()
                           << "Current User : " + this->m_DataBase.hostName()
                           << "Tables : ";
                                for(int i=0; i<TablesList.count();i++)
                                {
                                    this->m_Infos_Database << "        " + TablesList[i];
                                }
    this->m_Infos_Database << "----------------------------------------< END >----------------------------------------";

    return this->m_Infos_Database;
}

bool CSQLite_Local_DB::Connect_DB()
{
    bool Result;

    // Find QSLite driver
    this->m_DataBase = QSqlDatabase::addDatabase("QSQLITE");

    //Set database name
    this->m_DataBase.setDatabaseName(this->m_DatabaseName);

    if(this->m_DataBase.open())
    {
        Result = true;  // Open database : OK
    }
    else
    {
        Result = false; // Open database : Fail
    }
    return Result;
}

bool CSQLite_Local_DB::SendQuery(QString Query)
{
    QSqlQuery query(this->m_DataBase);
    bool Result = false;

    if(query.exec(Query))
    {
        SavePerfomAction("[WARNING] EXTERN CALL",Query);
        Result = true;
    }

    return Result;
}

QList<struct_DoorsStatus> CSQLite_Local_DB::SendQueryDoorsStatus(QString Query)
{
    QSqlQuery query(this->m_DataBase);
    QList<struct_DoorsStatus> DoorsStatusList;
    struct_DoorsStatus DoorsStatusTmp;

    SavePerfomAction("[WARNING] EXTERN CALL (DoorsStatus)",Query);
    if(query.exec(Query))
    {
        while(query.next())
        {
            DoorsStatusTmp.BoxNumber = query.value(2).toInt();
            DoorsStatusTmp.DoorIsOpen = query.value(3).toBool();
            DoorsStatusTmp.DoorIsLock = query.value(4).toBool();

            DoorsStatusList.append(DoorsStatusTmp);
        }
    }

    return DoorsStatusList;
}

bool CSQLite_Local_DB::Delete_DB()
{
    // Close database
    this->m_DataBase.close();

    // Remove created database file
    return QFile::remove(this->m_DatabaseName);
}

QString CSQLite_Local_DB::lastError()
{
    // If opening database has failed user can ask
    return m_DataBase.lastError().text();
}

int CSQLite_Local_DB::Login(QString IndentifiactionCode)
{
    int UserType = -4;
    QSqlQuery query(this->m_DataBase);

    QString CompanyPass;
    CompanyPass.append(QString(IndentifiactionCode[0]));
    CompanyPass.append(QString(IndentifiactionCode[1]));
    CompanyPass.append(QString(IndentifiactionCode[2]));
    bool CompanyPassChecked = true;

    QString PersonalPass;
    PersonalPass.append(QString(IndentifiactionCode[3]));
    PersonalPass.append(QString(IndentifiactionCode[4]));
    PersonalPass.append(QString(IndentifiactionCode[5]));
    bool PersonalPassChecked = true;

    QString PassWord;
    PassWord.append(QString(IndentifiactionCode[6]));
    PassWord.append(QString(IndentifiactionCode[7]));
    PassWord.append(QString(IndentifiactionCode[8]));
    PassWord.append(QString(IndentifiactionCode[9]));
    PassWord.append(QString(IndentifiactionCode[10]));
    PassWord.append(QString(IndentifiactionCode[11]));
    bool PassWordChecked = true;

    //Research user type with : Company Pass,Personal Pass,PassWord and check which one is a mistake.
    SavePerfomAction("User","SELECT UserType");
    if(query.exec("SELECT UserType FROM User WHERE UserCompanyPass = '"+CompanyPass+"' AND UserPersonalPass = '"+PersonalPass+"' AND UserPassWord = '"+PassWord+"';"))
    {
         if(query.next())
         {
            UserType = query.value(0).toInt();
            qDebug() << "UserType (query)" << UserType;
         }

         //identify which one are an error.
         SavePerfomAction("User","SELECT UserCompanyPass");
         if(query.exec("SELECT UserCompanyPass FROM User WHERE UserCompanyPass = '"+CompanyPass+"'"))
         {
             if(query.next())
                 qDebug() << "UserCompanyPass : OK";
             else
             {
                 qDebug() << "UserCompanyPass : Undefined";
                 UserType = UNDEFINED_COMPANY_PASS; //UserCompanyPass : Undefined
                 CompanyPassChecked = false;
             }
         }
         SavePerfomAction("User","SELECT UserPersonalPass");
         if(query.exec("SELECT UserPersonalPass FROM User WHERE UserPersonalPass = '"+PersonalPass+"'"))
         {
             if(query.next())
                 qDebug() << "UserPersonalPass : OK";
             else
             {
                 qDebug() << "UserPersonalPass : Undefined";
                 UserType = UNDEFINED_PERSONAL_PASS; //UserPersonalPass : Undefined
                 PersonalPassChecked = false;
             }
         }
         SavePerfomAction("User","SELECT UserPassWord");
         if(query.exec("SELECT UserPassWord FROM User WHERE UserPassWord = '"+PassWord+"'"))
         {
             if(query.next())
                 qDebug() << "UserPassWord : OK";
             else
             {
                 qDebug() << "UserPassWord : Undefined";
                 UserType = UNDEFINED_PASSWORD; //UserPassWord : Undefined
                 PassWordChecked = false;
             }
         }
    }
    if(!CompanyPassChecked && !PersonalPassChecked && !PassWordChecked)
        UserType = UNDEFINED_USER; //User : Unknown

    qDebug() << "UserType (return)" << UserType;
    return UserType;
}

bool CSQLite_Local_DB::SavePerfomAction(QString Table,QString Action)
{
    bool Result;
    QSqlQuery query(this->m_DataBase);
    QString TimeStamp;

    TimeStamp = QDateTime::currentDateTimeUtc().toString();
    if(query.exec("INSERT INTO PerformedActions (EditedTable,ActionMessage,Time) VALUES ('"+Table+"','"+Action+"','"+TimeStamp+"')"))
    {
         Result = true;
    }
    else
    {
         Result = false;
    }
    qDebug() << "SavePerfomAction Timestamp : "<< TimeStamp;
    return Result;
}

int CSQLite_Local_DB::CheckExtractCode(QString ExtractCode)
{
    int Result;
    QString TimeStampExtractCodeDB;
    QSqlQuery query(this->m_DataBase);

    Result = -1;
    SavePerfomAction("ExtractCode","SELECT idExtractCode");
    if(query.exec("SELECT idExtractCode FROM ExtractCode WHERE idExtractCode='"+ExtractCode+"'"))
    {
        while(query.next())
        {
            SavePerfomAction("ExtractCode","SELECT ExtractCodeExpiryTime");
            if(query.exec("SELECT ExtractCodeExpiryTime FROM ExtractCode WHERE idExtractCode='"+ExtractCode+"'"))
            {
                while(query.next())
                {
                    TimeStampExtractCodeDB = query.value(0).toString();

                    QDateTime TimeStampExtractCode;
                    QDateTime TimeStampNow;
                    TimeStampExtractCode = QDateTime::fromString(TimeStampExtractCodeDB);
                    TimeStampNow = TimeStampNow.currentDateTimeUtc();

                    qDebug()<< "TimeStampExtractCode : " <<TimeStampExtractCode.toString();
                    qDebug()<< "TimeStampNow :         " <<TimeStampNow.toString();

                    if(TimeStampExtractCode > TimeStampNow)
                        Result = 1; //ExtractCode exist and is valid
                    else
                        return 0; //ExtractCode is invalid
                }
            }
        }
    }

    return Result;
}

bool CSQLite_Local_DB::DeleteExtractCode(QString UsedExtractCode)
{
    bool Result = false;
    QSqlQuery query(this->m_DataBase);
    QList<int> IdBoxUsed;
    QStringList IdPackage;

    IdBoxUsed.append(-1);
    SavePerfomAction("Package","SELECT Linked_idBox");
    if(query.exec("SELECT Linked_idBox FROM Package WHERE Linked_idExtractCode='"+UsedExtractCode+"'"))
    {
        while(query.next())
        {
            IdBoxUsed << query.value(0).toInt();
            qDebug()<< "Get IdBoxUsed : "<<IdBoxUsed;
        }
    }
    SavePerfomAction("Package","SELECT idPackage");
    if(query.exec("SELECT idPackage FROM Package WHERE Linked_idExtractCode='"+UsedExtractCode+"'"))
    {
        while(query.next())
        {
            IdPackage << query.value(0).toString();
            qDebug()<< "Get IdPackage : "<<IdPackage;
        }
    }

    SavePerfomAction("ExtractCode","DELETE idExtractCode");
    if(query.exec("DELETE FROM ExtractCode WHERE idExtractCode='"+UsedExtractCode+"'"))
    {
        qDebug()<< "ExtractCode Delete...";

        //Delete packages, set empty box with id
        for(int i=0; i<IdPackage.count(); i++)
        {
            SavePerfomAction("Package","DELETE idPackage");
            if(query.exec("DELETE FROM Package WHERE idPackage ='"+IdPackage[i]+"'"))
            {
                for(int j=0; j<IdBoxUsed.count(); j++)
                {
                    SavePerfomAction("Box","UPDATE BoxIsUsed");
                    if(query.exec("UPDATE Box SET BoxIsUsed='false' WHERE idBox='"+QString::number(IdBoxUsed[j],10)+"'"))
                    {
                        SavePerfomAction("Doorlocker","UPDATE DoorLocker_LockState");
                        query.exec("UPDATE Doorlocker SET DoorLocker_LockState='true' WHERE linked_idDoor='"
                                   +QString::number(IdBoxUsed[j],10)+"'");

                        Result = true;
                        qDebug()<< "Get IdBoxUsed";
                        qDebug()<< "ExtractCode completly deleted !";
                    }
                }
            }
        }
    }
    return Result;
}

QList<int> CSQLite_Local_DB::GetFreeBoxes()
{
    QSqlQuery query(this->m_DataBase);
    QList<int> FreeBoxes;

    SavePerfomAction("Box","SELECT idBox");
    if(query.exec("SELECT idBox FROM Box WHERE BoxIsUsed='false'"))
    {
         while (query.next())
         {
             FreeBoxes << query.value(0).toInt();
         }
    }
    else
    {
        FreeBoxes[0] = -1;
    }

    return FreeBoxes;   // /!\ FreeBoxes can be an empty list !
}

QList<int> CSQLite_Local_DB::GetBoxesListConsumer(QString ExtractCode)
{
    QSqlQuery query(this->m_DataBase);
    QList<int> BoxesList;
    QStringList idPackagesList;

    if(CheckExtractCode(ExtractCode) == 1)
    {
        SavePerfomAction("ExtractCode","SELECT Linked_idPackage");
        if(query.exec("SELECT Linked_idPackage FROM ExtractCode WHERE idExtractCode='"+ExtractCode+"'"))
        {
             while (query.next())
             {
                 idPackagesList << query.value(0).toString();
                 qDebug()<<idPackagesList;
             }

             if(!idPackagesList.isEmpty())
             {
                 for(int i=0; i<idPackagesList.count(); i++)
                 {
                     qDebug()<<"Start BoxesList ";
                     SavePerfomAction("Package","SELECT Linked_idBox");
                     if(query.exec("SELECT Linked_idBox FROM Package WHERE idPackage='"+idPackagesList[i]+"'"))
                     {
                         if(query.next())
                         {
                             BoxesList << query.value(0).toInt();
                             qDebug()<<BoxesList;
                         }
                     }
                     else
                     {
                         BoxesList.append(-1);
                     }
                 }
             }
             else
             {
                 BoxesList.append(-1);
             }
        }
        else
        {
            BoxesList.append(-1);
        }
    }
    else
    {
        BoxesList.append(-1);
    }

    return BoxesList;   // /!\ BoxesList can be an empty list !
}

QList<struct struct_DoorGeom> CSQLite_Local_DB::GetBoxesList()
{
    QSqlQuery query(this->m_DataBase);
    QList<struct struct_DoorGeom> BoxesList;

    SavePerfomAction("Box","SELECT *");
    if(query.exec("SELECT * FROM Box "))
    {
        bool BoxIsUsed;
        while (query.next())
        {
            struct_DoorGeom geom;

            geom.BoxNumber = query.value(0).toInt();
            geom.BoxSize = query.value(1).toString();
            BoxIsUsed = query.value(2).toBool();
            if(BoxIsUsed)
               geom.status = KO;
            else
                geom.status = OK;
            geom.x = query.value(5).toInt();
            geom.y = query.value(6).toInt();

            BoxesList << geom;
        }
    }
    return BoxesList;
}

bool CSQLite_Local_DB::UpdateLocalData(QList<struct struct_PackagesUseBox> UpdatedPackagesUseBoxList)
{
    bool Result;
    QSqlQuery query(this->m_DataBase);

    for(int i=0; i<UpdatedPackagesUseBoxList.count(); i++)
    {
        //New ExtractCode
        for(int j=0; j<UpdatedPackagesUseBoxList[i].BoxContainment.PackageDeliveryCodeList.count(); j++)
        {
            SavePerfomAction("ExtractCode","INSERT INTO");
            query.prepare("INSERT INTO ExtractCode (idExtractCode, Linked_idPackage, ExtractCodeExpiryTime)"
                          "VALUES(:idExtractCode,:Linked_idPackage,:ExtractCodeExpiryTime)");

            query.bindValue(":idExtractCode", UpdatedPackagesUseBoxList[i].BoxContainment.PackagesExtractCode);
            query.bindValue(":Linked_idPackage", UpdatedPackagesUseBoxList[i].BoxContainment.PackageDeliveryCodeList[j]);
            query.bindValue(":ExtractCodeExpiryTime", UpdatedPackagesUseBoxList[i].BoxContainment.ExtractCodeExpiryTime);
            query.exec();
        }

        //New Package
        for(int j=0; j<UpdatedPackagesUseBoxList[i].BoxContainment.PackageDeliveryCodeList.count(); j++)
        {
            SavePerfomAction("Package","INSERT INTO");
            query.prepare("INSERT INTO Package (idPackage, Linked_idExtractCode, Linked_idBox) "
                          "VALUES(:idPackage,:Linked_idExtractCode,:Linked_idBox)");

            query.bindValue(":idPackage", UpdatedPackagesUseBoxList[i].BoxContainment.PackageDeliveryCodeList[j]);
            query.bindValue(":Linked_idExtractCode", UpdatedPackagesUseBoxList[i].BoxContainment.PackagesExtractCode);
            query.bindValue(":Linked_idBox", UpdatedPackagesUseBoxList[i].BoxNumber);
            query.exec();
        }

        //Box update
        SavePerfomAction("Box","UPDATE BoxIsUsed");
        query.exec("UPDATE Box SET BoxIsUsed='true' WHERE idBox='"+QString::number(UpdatedPackagesUseBoxList[i].BoxNumber,10)+"'");
        SavePerfomAction("Doorlocker","UPDATE DoorLocker_LockState");
        query.exec("UPDATE Doorlocker SET DoorLocker_LockState='true' WHERE linked_idDoor='"+QString::number(UpdatedPackagesUseBoxList[i].BoxNumber,10)+"'");
        Result = true;
    }

    return Result;
}

QList<QString> CSQLite_Local_DB::ReadSQL_File(QString FilePath)
{
    QList<QString> QueryList;
    QString temp;
    QString RdyQuery;
    QFile SQL_File(FilePath);
    QTextStream SQL_FileStream(&SQL_File);
    temp = " ";

    if(SQL_File.open(QIODevice::ReadOnly))
    {
         while(!SQL_FileStream.atEnd())
         {
             while(!temp.contains(';'))
             {
                 temp = SQL_FileStream.readLine();
                 RdyQuery += temp;
             }
             QueryList.append(RdyQuery);
             qDebug()<<"Ready query : "<<RdyQuery;
             RdyQuery.clear();
             temp.clear();
         }
         SQL_File.close();
    }
    else
    {
        QueryList.clear();
    }

    return QueryList;
}

bool CSQLite_Local_DB::WriteSQL_File(QString FilePath, QString Data)
{
    bool Result = false;
    QFile SQL_File(FilePath);
    QTextStream Stream(&SQL_File);

    if(SQL_File.open(QIODevice::Append))
    {
        Stream << Data;
        //qDebug() << "Writed values : " <<ReadSQL_File(FilePath);
        Stream.flush();
        SQL_File.close();
        Result = true;
    }

    return Result;
}

bool CSQLite_Local_DB::SQL_Database_Manager(int Option)
{
    bool Result = false;
    QSqlQuery query(this->m_DataBase);
    QList<QString> QueryList;

    switch(Option)
    {
        case EMPTY_DATABASE:
        {
            QueryList = ReadSQL_File(this->m_SQL_File_DatabaseEmpty_Path);

            for(int i=0; i<QueryList.count(); i++)
            {
                query.exec(QueryList[i]);
                qDebug()<<"Query send : "<<QueryList[i];
            }
            Result = true;
            break;
        }
        case DEFAULT_DATABASE:
        {
            QueryList = ReadSQL_File(this->m_SQL_File_DatabaseDefault_Path);

            for(int i=0; i<QueryList.count(); i++)
            {
                query.exec(QueryList[i]);
                qDebug()<<"Query send : "<<QueryList[i];
            }
            Result = true;
            break;
        }
        case SAVE_DATABASE:
        {
            if(SaveDatabase(this->m_SQL_File_DatabaseLastSave_Path))
                Result = true;
            break;
        }
        case LOAD_SAVE_DATABASE:
        {
            if(LoadDatabaseSave(this->m_SQL_File_DatabaseLastSave_Path))
                Result = true;
            break;
        }
        default:
        {
            Result = false;
            break;
        }
    }

    return Result;
}

bool CSQLite_Local_DB::SaveDatabase(QString FilePath)
{
    bool Result = false;
    QList<QString> TablesList = this->m_DataBase.tables();
    QList<QString> EmptyDatabaseQueryList;
    QList<struct struct_Database_Contains> Database_Contains;
    struct struct_Database_Contains Database_Contains_Temp;
    QSqlQuery query(this->m_DataBase);

    EmptyDatabaseQueryList = ReadSQL_File(m_SQL_File_DatabaseEmpty_Path);
    for(int i=0; i<EmptyDatabaseQueryList.count(); i++)
    {
        WriteSQL_File(FilePath,EmptyDatabaseQueryList[i]+"\n");
    }

    for(int Table=0; Table<TablesList.count(); Table++)
    {
        Database_Contains_Temp.Table = TablesList[Table];
        if(query.exec("SELECT * FROM " + TablesList[Table]))
        {
            qDebug()<<"SaveDatabase : SELECT ALL" << TablesList[Table];
            while(query.next())
            {
                QString QueryValue;

                for(int Col=0; Col<=9; Col++)
                {
                    if(query.value(Col).toString() != "")
                    {
                        QueryValue += "'"+query.value(Col).toString()+"'" + ",";

                        Database_Contains_Temp.Values.append(QueryValue);
                    }
                }
                QueryValue.replace(QueryValue.size()-1,sizeof(QChar)," ");
                WriteSQL_File(FilePath,"INSERT INTO "+TablesList[Table]+" VALUES("+QueryValue+");\n");
                QueryValue.clear();
            }
        }
        Database_Contains.append(Database_Contains_Temp);
        Database_Contains_Temp.Values.clear();
        Result = true;
    }

    return Result;
}

bool CSQLite_Local_DB::LoadDatabaseSave(QString FilePath)
{
    bool Result;
    QFile SQL_File(FilePath);
    QList<QString> QueryList;
    QSqlQuery query(this->m_DataBase);

    if(SQL_File.exists())
    {
        Result = true;
        QueryList = ReadSQL_File(FilePath);
        for(int i=0; i<QueryList.count(); i++)
        {
            query.exec(QueryList[i]);
        }
    }
    else
    {
        Result = false;
    }
    return Result;
}

bool CSQLite_Local_DB::SendQueryDoorsIsClosed(QString Query)
{
    QSqlQuery query(this->m_DataBase);
    bool Result = false;

    SavePerfomAction("[WARNING] EXTERN CALL (DoorsIsClosed)",Query);
    if(query.exec(Query))
    {
        while (query.next())
        {
            Result = query.value(3).toBool();
            if(Result == false)
                return Result;
        }
    }

    return Result;
}

