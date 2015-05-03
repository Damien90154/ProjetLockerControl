#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H


#include<QString>
#include<QList>

// RebuildDatabase options
#define EMPTY_DATABASE 1
#define DEFAULT_DATABASE 2
#define SAVE_DATABASE 3
#define LOAD_SAVE_DATABASE 4

// Logging errors
#define UNDEFINED_USER -4
#define UNDEFINED_COMPANY_PASS -3
#define UNDEFINED_PERSONAL_PASS -2
#define UNDEFINED_PASSWORD -1
#define LIVREUR 0
#define MAINTENANCE 1

// struct_DoorGeom
#define OK 0
#define KO 1
#define SELECTED 2

struct struct_PackagesUseBox
{
    int BoxNumber;
    struct struct_BoxContainment
    {
        QString PackagesExtractCode;
        QString ExtractCodeExpiryTime;
        QList<QString> PackageDeliveryCodeList;
    }BoxContainment;
};

struct struct_DoorGeom
{
    int BoxNumber;
    QString BoxSize;
    int status;
    int x;
    int y;
};

struct struct_Database_Contains
{
    QString Table;
    QList<QString> Values;
};

struct struct_DoorsStatus
{
    int BoxNumber;
    bool DoorIsOpen;
    bool DoorIsLock;
};



#endif // DATASTRUCTURES_H
