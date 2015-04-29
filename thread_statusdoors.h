#ifndef THREAD_STATUSDOORS_H
#define THREAD_STATUSDOORS_H

#include <QThread>
#include "DataStructures.h"
#include "cdoors.h"


class Thread_StatusDoors : public QThread
{
    Q_OBJECT

public:
    Thread_StatusDoors(CDoors *Cdoors);
    ~Thread_StatusDoors();
    void setListBox(QList<int> list);

    void stopThread();
    void run();

signals :
    void StatuDoor(struct struct_DoorsStatus);

private:
    QList<int> m_listdoors;
    CDoors *m_CDoors;
    bool m_termined;


};

#endif // THREAD_STATUSDOORS_H
