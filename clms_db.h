#ifndef CLMS_DB_H
#define CLMS_DB_H

#include "DataStructures.h"

class CLMS_DB
{
    private :
        QString randString(int len);

    public:
        CLMS_DB();
        QList<struct struct_PackagesUseBox> GenerateExtractCode(QList<struct struct_PackagesUseBox> PackageStorageListEmpty);
        QList<QString> Get_LastDatabase_Save(QString DB_Site);
        bool AutoSave_DatabaseLMS(QString DB_Site, QString FilePath);
        bool ManualSave_DatabaseLMS(QString DB_Site, QString FilePath);
};

#endif // CLMS_DB_H
