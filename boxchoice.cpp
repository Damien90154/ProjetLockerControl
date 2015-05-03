#include "boxchoice.h"
#include "ui_boxchoice.h"

#include <QDebug>
#include <QGraphicsTextItem>
#include <QToolTip>

#define HEIGHT 100
#define WIDTH  100
#define STARTX 0
#define STARTY 0

BoxChoice::BoxChoice(MenuDelivery *WMenuDelivery,CSQLite_Local_DB *bd,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoxChoice)
{
    ui->setupUi(this);

    m_BD = bd;
    m_WMenuDelivery = WMenuDelivery;

    //connexion boutons
    connect(ui->B_Valide,SIGNAL(clicked()),this,SLOT(ValidBox()));
    connect(ui->B_Cancel,SIGNAL(clicked()),this,SLOT(Cancel()));
    connect(m_WMenuDelivery,SIGNAL(refreshGraphicsBox()),this,SLOT(Refresh()));

    //creation de la scene
    m_Scene = new QGraphicsScene(this);
    ui->G_Show_Box->setScene(m_Scene);

    //récupération de la liste des box
    m_ListBox.append(m_BD->GetBoxesList());

    createBoxes();

}

QGraphicsView* BoxChoice::GetGraphicsView()
{
    return ui->G_Show_Box;
}

QGraphicsScene* BoxChoice::GetScene()
{
    return m_Scene;
}

BoxChoice::~BoxChoice()
{
    delete ui;
}

void BoxChoice::retranslateUi()
{
    ui->retranslateUi(this);
}

void BoxChoice::ValidBox()
{
    QList<int> boxSelected;

    boxSelected = GetBoxSelected();
    if(boxSelected.isEmpty()){
        //message alerte

       int x;
       int y;
       x = mapToGlobal(ui->B_Assistance->pos()).x()+ui->B_Assistance->width()+10;
       y =  mapToGlobal(ui->B_Assistance->pos()).y()-10;
       QToolTip::showText(QPoint(x,y),tr("Attention!!!<br/> Vous n'avez pas s&eacute;lectionn&eacute; de consigne."),ui->B_Assistance);
    }
    else{
        emit SendListBoxSelected(boxSelected);
        m_ShowWidgets->ShowWScanPackage();
    }

}

QList<int> BoxChoice::GetBoxSelected()
{
    QList<int> boxSelected;
     for(int i = 0;i < m_ListBox.size(); i++)
     {
         if(m_ListBox[i].status == SELECTED)
         {
             boxSelected << m_ListBox[i].BoxNumber;
         }
     }
     return boxSelected;
}

void BoxChoice::Cancel()
{
    //retour au menu de livraison
    m_ShowWidgets->ShowWMenuDelivery();
}


void BoxChoice::createBoxes()
{
    int height;
    int posX;
    int posY;

    qDebug()<<"Nombre de consignes : "<<m_ListBox.size();

    for (int i=0; i < m_ListBox.size(); i++)
    {
        qDebug()<< "numéro du casier : " << i;

        //on donne un id pour repérer le clic de la souris
        drawBox *box = new drawBox(i);

        posX = STARTX + m_ListBox[i].x*WIDTH;
        posY = STARTY + m_ListBox[i].y*HEIGHT;

        if ((m_ListBox[i].BoxSize.compare("A")==0) || (m_ListBox[i].BoxSize.compare("AW")==0)) //casier simple
        {
            height = HEIGHT;
        }
        if (m_ListBox[i].BoxSize.compare("CM")==0 || (m_ListBox[i].BoxSize.compare("CW")==0)) //casier double
        {
            height = HEIGHT*2;
        }

        box->drawRect(posX,posY, WIDTH, height);

        box->setColor(m_ListBox[i].status);

        QGraphicsTextItem *text = new QGraphicsTextItem(box);
        text->setPlainText(QString::number(m_ListBox[i].BoxNumber));

        //position du text
        text->setPos(posX,posY);

        m_Scene->addItem(box);

        connect(box,SIGNAL(MyId(int)),this,SLOT(manageRect(int)));

        //pour changer la couleur
        m_listdrawBox << box;
    }
}


void BoxChoice::manageRect(int id)
{
    switch (m_ListBox[id].status)
    {
        case  OK :
            m_ListBox[id].status = SELECTED;
            break;

        case  SELECTED :
            m_ListBox[id].status = OK;
            break;

        default :
        break;
    }
    m_listdrawBox[id]->setColor(m_ListBox[id].status);

}
void BoxChoice::manageDoorUnvailable(int id)
{
    switch (m_ListBox[id].status)
    {

        case  KO:
                 m_ListBox[id].status = OK;
                 break;

        default :
                 m_ListBox[id].status = KO;
                 break;
    }
    m_listdrawBox[id]->setColor(m_ListBox[id].status);

}

void BoxChoice::Refresh(){

   m_Scene->clear();
   m_listdrawBox.clear();
   ui->G_Show_Box->update();
   m_ListBox.clear();
   m_ListBox.append(m_BD->GetBoxesList());
   createBoxes();
   update();

}


