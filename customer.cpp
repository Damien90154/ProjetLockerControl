#include "customer.h"
#include "ui_customer.h"
#include <QRegExpValidator>
#include<QToolTip>
#include <QDebug>


#define VALID   1
#define UNVALID 0

Customer::Customer(CSQLite_Local_DB *bd, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Customer)
{
    ui->setupUi(this);
    m_BD = bd;
    m_ShowWidgets = NULL;

    QRegExpValidator *reVal = new QRegExpValidator( QRegExp("^(([0-9])|([A-Z])|([a-z]))+$"), this );
    ui->lineEdit->setValidator(reVal);

    connect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SLOT(Upper(QString)));
    connect(this,SIGNAL(TextToUpper(QString)),ui->lineEdit,SLOT(setText(QString)));

    connect(ui->B_Home,SIGNAL(clicked()),this,SLOT(ShowHome()));
    connect(ui->WKeyBoard,SIGNAL(SendCarac(QChar)),this,SLOT(SetCaract(QChar)));
    connect(ui->WKeyBoard,SIGNAL(SupprLastCaract()),this,SLOT(SupprCaract()));
    connect(ui->WKeyBoard,SIGNAL(ButtonOKCliked()),this,SLOT(Valid_Code()));

    ui->WKeyBoard->setVisible(true);


}

Customer::~Customer()
{
    delete ui;
}

void Customer::retranslateUi()
{
    ui->retranslateUi(this);
    ui->WKeyBoard->retranslateUi();
    ui->WKeyBoard->setTextButtonOK(tr("Valider"));
}

void Customer::ShowHome()
{
    ui->lineEdit->clear();
    m_ShowWidgets->ShowWConsoleWindows();
}

void Customer::Upper(QString str)
{
    str = str.toUpper();
    emit TextToUpper(str);
}

void Customer::Valid_Code()
{
    int result;
    QString ExtractCode;
    m_listboxcustomer.clear();
    ExtractCode = ui->lineEdit->text();

    if(ExtractCode.compare("")!=0)
    {

        //verification du code de retrait dans la BD Local

          result = m_BD->CheckExtractCode(ExtractCode);
          qDebug()<<"result verif code retrait:"<<result;

         //si le code de retrait est valide
            //demande d'ouverture des consignes consernées
          if(result == VALID)
          {

              m_listboxcustomer = m_BD->GetBoxesListConsumer(ExtractCode);

              //envoi la liste des portes selectionner et le code de retrait
              emit SendListbox(m_listboxcustomer);
              emit SendCode(ExtractCode);

              //affichage des consignes ouvertes
              m_ShowWidgets->ShowWPackageBox();

          }
          else{
              //sinon code incorrecte
              int x;
              int y;
              x=ui->B_Assistance->x()-350;
              y = ui->B_Assistance->y();
              QToolTip::showText(QPoint(x,y),tr("Erreur!!!<br/> Le code de retrait est incorrect.<br/> Veuillez réessayer."),this);
          }
    }
    else{
        QPoint pos;
        pos.setX(ui->lineEdit->x() + 250);
        pos.setY(ui->lineEdit->y() + 50);
        QToolTip::showText(pos,tr("Erreur!!!,Vous n'avez rien tapez"),this);

    }

    ui->lineEdit->clear();

}

void Customer::SetCaract(QChar caract)
{
    QString text;
    text = ui->lineEdit->text();
    ui->lineEdit->setText(text.append(caract));
}

void Customer::SupprCaract()
{
    QString text;
    int taille;

    taille = ui->lineEdit->text().size();
    text = ui->lineEdit->text().remove(taille-1,1);
    ui->lineEdit->setText(text);
}



