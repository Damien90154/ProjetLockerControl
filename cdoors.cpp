#include "cdoors.h"
#include <QDebug>

CDoors::CDoors(CSQLite_Local_DB *BD)
{
    LC_DataBase = BD;
    if(!LC_DataBase->Get_DataBaseIsReady())
        qDebug()<<"[WARNING] No database connection !";
    m_compt=10;
}

bool CDoors::OpenDoors(QList<int> DoorsList)
{
    for(int i=0; i<DoorsList.count();i++)
    {
        qDebug() << "Opening door : " << DoorsList[i];
        LC_DataBase->SendQuery("UPDATE DoorLocker SET DoorLocker_OpenState='true' WHERE Linked_idDoor='"+QString::number(DoorsList[i],10)+"'");
    }
    return true;
}

bool CDoors::CloseDoors(QList<int> DoorsList)
{
    for(int i=0; i<DoorsList.count();i++)
    {
        qDebug() << "Closing door : " << DoorsList[i];
        LC_DataBase->SendQuery("UPDATE DoorLocker SET DoorLocker_OpenState='false' WHERE Linked_idDoor='"+QString::number(DoorsList[i],10)+"'");
    }
    return true;
}

bool CDoors::LockDoors(QList<int> DoorsList)
{
    for(int i=0; i<DoorsList.count();i++)
    {
        qDebug() << "Locking door : " << DoorsList[i];
        LC_DataBase->SendQuery("UPDATE DoorLocker SET DoorLocker_LockState='true' WHERE Linked_idDoor='"+QString::number(DoorsList[i],10)+"'");
    }
    return true;
}

bool CDoors::UnlockDoors(QList<int> DoorsList)
{
    for(int i=0; i<DoorsList.count();i++)
    {
        qDebug() << "Unlocking door : " << DoorsList[i];
        LC_DataBase->SendQuery("UPDATE DoorLocker SET DoorLocker_LockState='false' WHERE Linked_idDoor='"+QString::number(DoorsList[i],10)+"'");
    }
    return true;
}

bool CDoors::DoorsIsClosed(QList<int> DoorsList)
{
    bool Result = false;

    for(int i=0; i<DoorsList.count(); i++)
    {
        Result = LC_DataBase->SendQueryDoorsIsClosed("SELECT * FROM DoorLocker WHERE DoorLocker_OpenState='true' AND Linked_idDoor='"
                                                    +QString::number(DoorsList[i],10)+"'");
        if(Result == false)
            return Result;
    }

    return Result;
}

QList<struct_DoorsStatus> CDoors::DoorsStatus(QList<int> DoorsList)
{
    QList<struct_DoorsStatus> DoorsStatusListComplete;
    QList<struct_DoorsStatus> DoorsStatusList;
    struct_DoorsStatus DoorsStatusTemp;
    qDebug() << "Doorsttatus : ";
    DoorsStatusListComplete = LC_DataBase->SendQueryDoorsStatus("SELECT * FROM DoorLocker");
    for(int i=0; i<DoorsStatusListComplete.size(); i++)
    {
        for(int j=0; j<DoorsList.size();j++)
        {
            if( DoorsStatusListComplete[i].BoxNumber == DoorsList[j] )
            {
                DoorsStatusTemp.BoxNumber = DoorsStatusListComplete[i].BoxNumber;
                DoorsStatusTemp.DoorIsOpen = DoorsStatusListComplete[i].DoorIsOpen;
                DoorsStatusTemp.DoorIsLock = DoorsStatusListComplete[i].DoorIsLock;
                DoorsStatusList.append(DoorsStatusTemp);
                qDebug() << "Door : " << DoorsStatusTemp.BoxNumber << "added";
            }
        }
    }

    if(DoorsIsClosed(DoorsList))
    {
        m_compt-=1;


    if(m_compt == 0)
    {
        CloseDoors(DoorsList);
        m_compt=10;
    }
    }
    return DoorsStatusList;
}
