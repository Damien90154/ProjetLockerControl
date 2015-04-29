#include "clms_db.h"
#include "DataStructures.h"
#include <QDateTime>
#include <QDebug>

CLMS_DB::CLMS_DB()
{
}

QString CLMS_DB::randString(int len)
{
    QString str;
    QTime Time = QTime::currentTime();
    int RandomNumber;

    str.resize(len);
    for (int i = 0; i<len ; i++)
    {
        RandomNumber = (Time.second()*Time.minute()+Time.msec())+qrand();
        str[i] = QChar('A' + char(RandomNumber % ('Z' - 'A')));
    }
    return str;
}

QList<struct struct_PackagesUseBox> CLMS_DB::GenerateExtractCode(QList<struct struct_PackagesUseBox> PackageStorageListEmpty)
{
    QString ExtractCode;
     ExtractCode = randString(10);

    if (!PackageStorageListEmpty.isEmpty())
    {
        for(int i=0; i<PackageStorageListEmpty.count(); i++)
        {

            qDebug() << ExtractCode;
            PackageStorageListEmpty[i].BoxContainment.PackagesExtractCode.append(ExtractCode);

            QDateTime TimeStampExpiryTime;
            TimeStampExpiryTime = TimeStampExpiryTime.currentDateTimeUtc();
            TimeStampExpiryTime = TimeStampExpiryTime.addDays(14);
            PackageStorageListEmpty[i].BoxContainment.ExtractCodeExpiryTime = TimeStampExpiryTime.toString();
        }
    }
    return PackageStorageListEmpty;
}
