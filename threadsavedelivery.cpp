#include "threadsavedelivery.h"
#include "deliveryconfirm.h"

ThreadSaveDelivery::ThreadSaveDelivery(CSQLite_Local_DB *db, CLMS_DB *lms,DeliveryConfirm *WDeliveryConfirm):QThread()
{
    m_DB = db;
    m_LMS = lms;
    m_WDeliveryConfirm = WDeliveryConfirm;
    connect(m_WDeliveryConfirm,SIGNAL(SendListPackage(QList<struct_PackagesUseBox>)),this,SLOT(startThread(QList<struct_PackagesUseBox>)));

}

ThreadSaveDelivery::~ThreadSaveDelivery()
{

}

void ThreadSaveDelivery::run()
{
    int value = 12;

    emit SetValueProgress(value);

    //transmission de la liste au serveur LMS et renvoie le code de retrait
    m_Packageslist = m_LMS->GenerateExtractCode(m_tempPackageList);

    for(value = 13;value <=50; value++)
    {
        emit SetValueProgress(value);
        msleep(100);
    }

    //envoie la liste avec code retrait a  la BD Local
    m_DB->UpdateLocalData(m_Packageslist);
    for(value=50;value <=100; value++)
    {
        emit SetValueProgress(value);
        msleep(100);
    }
    finished();
    exit();
}

void ThreadSaveDelivery::startThread(QList<struct_PackagesUseBox> listpackage)
{
    m_Packageslist.clear();
    m_tempPackageList.clear();
    m_tempPackageList = listpackage;
    start();
}
