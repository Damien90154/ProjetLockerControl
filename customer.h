#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QWidget>
#include "showwidgets.h"
#include "csqlite_local_db.h"
#include "showpackagebox.h"


namespace Ui {
class Customer;
}

class Customer : public QWidget
{
    Q_OBJECT

public:
    explicit Customer(CSQLite_Local_DB*, QWidget *parent = 0);
    void SetShowWidgets(ShowWidgets *TShowWidgets){m_ShowWidgets = TShowWidgets;}


    ~Customer();

    void retranslateUi();
public slots:
    void Valid_Code();
    void Upper(QString);
    void ShowHome();

signals:
    void SendListbox(QList<int>);
    void SendCode(QString);
    void refresh();
    void TextToUpper(QString);

private slots:
    void SetCaract(QChar caract);
    void SupprCaract();

private:
    Ui::Customer *ui;

    CSQLite_Local_DB *m_BD;
    ShowWidgets *m_ShowWidgets;
    QList<int> m_listboxcustomer;
    ShowPackageBox *m_Widget_ShowPackageBox;


};

#endif // Customer_H
