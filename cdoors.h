#ifndef CDOORS_H
#define CDOORS_H

#include "DataStructures.h"
#include "csqlite_local_db.h"

class CDoors
{
private :
    CSQLite_Local_DB *LC_DataBase;
    int m_compt;
public:
    CDoors(CSQLite_Local_DB *BD);
    bool OpenDoors(QList<int> DoorsList);
    bool CloseDoors(QList<int> DoorsList);
    bool LockDoors(QList<int> DoorsList);
    bool UnlockDoors(QList<int> DoorsList);
    QList<struct_DoorsStatus> DoorsStatus(QList<int> DoorsList);
    bool DoorsIsClosed(QList<int> DoorsList);
};

#endif // CDOORS_H
