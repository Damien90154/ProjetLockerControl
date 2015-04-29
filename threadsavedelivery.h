#ifndef THREADSAVEDELIVERY_H
#define THREADSAVEDELIVERY_H

#include <QThread>
#include "clms_db.h"
#include "csqlite_local_db.h"
#include "DataStructures.h"
class DeliveryConfirm;

class ThreadSaveDelivery : public QThread
{
    Q_OBJECT
    public:
        ThreadSaveDelivery(CSQLite_Local_DB *db, CLMS_DB *lms,DeliveryConfirm *WDeliveryConfirm);
        ~ThreadSaveDelivery();
        void run();
    public slots:
        void startThread(QList<struct_PackagesUseBox> listpackage);

    signals:
        void SetValueProgress(int);

    private:
        QList<struct_PackagesUseBox> m_tempPackageList;
        QList<struct_PackagesUseBox> m_Packageslist;
        CSQLite_Local_DB *m_DB;
        CLMS_DB *m_LMS;
        DeliveryConfirm *m_WDeliveryConfirm;


};

#endif // THREADSAVEDELIVERY_H
