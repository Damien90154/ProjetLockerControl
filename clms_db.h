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
};

#endif // CLMS_DB_H
