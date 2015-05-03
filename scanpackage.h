#ifndef SCANPACKAGE_H
#define SCANPACKAGE_H

#include <QWidget>

#include "showwidgets.h"
#include "DataStructures.h"
#include "boxchoice.h"
#include "custompushbutton.h"

namespace Ui {
class ScanPackage;
}

class ScanPackage : public QWidget
{
    Q_OBJECT

public:
    explicit ScanPackage(BoxChoice *,QWidget *parent = 0);
    ~ScanPackage();
    void SetShowWidgets(ShowWidgets *TShowWidgets){m_ShowWidgets = TShowWidgets;}
    bool isNumBoxExist(int numbox);
    int  getIndexListNumBoxExist(int numbox);
    void AddItemListWidget(QString NumPackage);
    void Refresh();
    int BuildingListPackages(); //construction de la QList<struct_PackagesUseBox>
    void retranslateUi();
    bool isExistNumPackage(QString NumPackage);

public slots:
    void StockNumberPackage();//stock les n°colis dans une qlist
    void ValidateDelivery();//recuperation de la liste des colis et demande de confirmation
    void CancelDelivery();//annule la saisie des colis pour la consigne
    void ConfirmValidate();
    void ReturnListPackage();
    void ReceiveListBoxSelected(QList<int>);
    void DeleteNumPackage(QString package);
    void Upper(QString str);

signals :
    void SendListPackageBox(QList<struct_PackagesUseBox> );
    void ShowStowPackage();
    void TextToUpper(QString);

private slots:
    void SetManual();
    void SetScanner();
    void ChangePage();
    void SetCaract(QChar caract);
    void SupprCaract();

private:
    Ui::ScanPackage *ui;
    ShowWidgets *m_ShowWidgets;
    BoxChoice *m_WBoxChoice;


    QList<struct_PackagesUseBox> m_listPackageBox;
    QList<QString> m_ListPackagesString;
    QList<int> m_ListBoxselected;
    QList<CustomPushButton *> m_ListCustPusButton;
    int m_idPushButton;
    int m_page;

};

#endif // SCANPACKAGE_H
