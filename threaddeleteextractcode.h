#ifndef THREADDELETEEXTRACTCODE_H
#define THREADDELETEEXTRACTCODE_H

#include <QThread>
#include "csqlite_local_db.h"

class ShowPackageBox;


class ThreadDeleteExtractCode : public QThread
{
    Q_OBJECT
public:
    ThreadDeleteExtractCode(int id,CSQLite_Local_DB*, ShowPackageBox *WShowPackageBox);
    int getId(){return m_Id;}
    void run();

private:
    CSQLite_Local_DB *m_DB;
    QString m_ExtractCode;
    ShowPackageBox *m_WShowPackageBox;
    int m_Id;

signals:

void terminatedThread(int,bool);

public slots:
 void startThread(QString code);

};

#endif // THREADDELETEEXTRACTCODE_H
