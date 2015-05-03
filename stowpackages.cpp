#include "stowpackages.h"
#include "ui_stowpackages.h"
#include <QScrollBar>
#include <QToolTip>
#include <QDebug>

StowPackages::StowPackages(ScanPackage *WScanPackage, BoxChoice *WBoxChoice,CSQLite_Local_DB *DB,CDoors *doors ,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StowPackages)
{
    ui->setupUi(this);
    m_WScanPackage = WScanPackage;
    m_WBoxChoice = WBoxChoice;
    m_CDoors = doors;
    m_BD = DB;
    m_CustomTreeWidget = new CustomTreeWidget(ui->treeWidget);

    m_Scene = m_WBoxChoice->GetScene();
    ui->graphicsView->setScene(m_Scene);

    m_T_StatusDoors = new Thread_StatusDoors(m_CDoors);

    qRegisterMetaType< struct_DoorsStatus >( "struct_DoorsStatus" );
    connect(m_T_StatusDoors,SIGNAL(StatuDoor(struct_DoorsStatus)),this,SLOT(StatusDoors(struct_DoorsStatus)));
    connect(m_WScanPackage,SIGNAL(SendListPackageBox(QList<struct_PackagesUseBox>)),this,SLOT(ReceiveListPackageBox(QList<struct_PackagesUseBox>)));
    connect(m_WScanPackage,SIGNAL(ShowStowPackage()),this,SLOT(ShowStowP()));

    //boutons
    connect(ui->B_Cancel_Change,SIGNAL(clicked()),this,SLOT(ShowStowP()));
    connect(ui->B_ChangeBox,SIGNAL(clicked()),this,SLOT(ShowChangeBox()));
    connect(ui->B_Terminate,SIGNAL(clicked()),this,SLOT(StoragePackagesFinised()));
    connect(ui->B_Valid,SIGNAL(clicked()),this,SLOT(SaveBoxSelected()));
    connect(ui->B_Next_Change,SIGNAL(clicked()),this,SLOT(ValidCheckedbox()));
    connect(ui->B_Next_Pdef,SIGNAL(clicked()),this,SLOT(ValidCheckedboxdef()));
    connect(ui->B_Cancel_def,SIGNAL(clicked()),this,SLOT(ShowPageChangeBoxChecked()));
    connect(ui->B_Cancel_Selectbox,SIGNAL(clicked()),this,SLOT(ShowPageChangeBoxDefChecked()));

    ui->treeWidget->verticalScrollBar()->setFixedWidth(60);

}

StowPackages::~StowPackages()
{
    m_T_StatusDoors->stopThread();
    delete ui;
}

void StowPackages::ShowPageChangeBoxChecked()
{
    ui->stackedWidget->setCurrentWidget(ui->P_checkboxechange);
}
void StowPackages::ShowPageChangeBoxDefChecked()
{
    //remise a l'état initiale
    //mettre les portes qui etait non dsponible
    for(int i=0;i < m_listBoxdeftmp.size();i++)
    {
        m_WBoxChoice->manageDoorUnvailable((m_listBoxdeftmp[i]-1));
    }

    //mettre les portes qui ont un defaut en non disponible
    for(int i=0;i < m_listBoxdeftmp.size();i++)
    {
        m_WBoxChoice->manageRect((m_listBoxdeftmp[i]-1));
    }

    //déselectionne les portes qui sont selectionne
    for(int i=0;i < m_listBoxtmp.size();i++)
    {
        m_WBoxChoice->manageRect((m_listBoxtmp[i]-1));
    }

    ui->stackedWidget->setCurrentWidget(ui->P_CheckBoxDef);
}

void StowPackages::ReceiveListPackageBox(QList<struct_PackagesUseBox> listPackagebox)
{

    ResetAttribut();

    m_listPackageBox = listPackagebox;

    for(int i =0 ; i <m_listPackageBox.size();i++)
    {
       m_listBox << m_listPackageBox[i].BoxNumber;
    }

    CreateListBoxTreeWidget();
}

void StowPackages::ResetAttribut()
{
    m_CustomTreeWidget->ClearListItem();
    ui->treeWidget->clear();
    ui->ListBoxes->clear();
    ui->listBOX_checkDef->clear();
    m_listPackageBox.clear();
    m_listBox.clear();
}

void StowPackages::ShowDeliveryConfirm()
{
    emit ShowDeliveryC();
    m_ShowWidgets->ShowWDeliveryConfirm();
}

void StowPackages::StatusDoors(struct_DoorsStatus doorstatus)
{
    if(doorstatus.DoorIsOpen)
    {
        m_CustomTreeWidget->EditedItem_ColumnStatusOfDoor(doorstatus.BoxNumber,tr("OUVERT"),QColor(Qt::darkGreen));
        m_CustomTreeWidget->ButtonVisible(doorstatus.BoxNumber,true);
    }
    else{

        m_CustomTreeWidget->EditedItem_ColumnStatusOfDoor(doorstatus.BoxNumber,tr("FERME"),QColor(Qt::red));
        m_CustomTreeWidget->ButtonVisible(doorstatus.BoxNumber,false);
    }
}

void StowPackages::ShowStowP()
{

    ui->B_ChangeBox->setVisible(true);
    ui->stackedWidget->setCurrentIndex(0);

}

void StowPackages::AddItemListBox()
{
    for(int i =0 ;i<m_listBox.size();i++)
    {
        QListWidgetItem *item;
        item = new QListWidgetItem(QString("Porte : "+QString::number(m_listBox[i])));
        item->setCheckState(Qt::Unchecked);
        ui->ListBoxes->addItem(item);
    }

}

void StowPackages::ShowChangeBox()
{
    ui->B_ChangeBox->setVisible(false);
    ui->ListBoxes->clear();


    //ajoute liste des boxes
    AddItemListBox();
    ui->stackedWidget->setCurrentWidget(ui->P_checkboxechange);

}

void StowPackages::ValidCheckedbox()
{
    ui->listBOX_checkDef->clear();

    QList<QListWidgetItem*> listitemtmp;


    //si listbox empty message alerte
    if(!m_listBox.isEmpty())
    {
        for(int i=0;i<m_listBox.size();i++)
        {
            //recupere les items

            QListWidgetItem *item;
            item = new QListWidgetItem(QString("Porte : "+QString::number(m_listBox[i])));
            item->setCheckState(Qt::Unchecked);
            listitemtmp << item;

        }

        for(int i=0;i<ui->ListBoxes->count();i++)
        {
            if(ui->ListBoxes->item(i)->checkState() == Qt::Checked)
            {
                //recupere les items ckecked
                listitemtmp[i]->setCheckState(Qt::Unchecked);
                ui->listBOX_checkDef->addItem(listitemtmp[i]);

            }
        }
        if(ui->listBOX_checkDef->count() == 0)
        {
            qDebug()<<"aucune porte selectionné";
        }
        else{
              ui->stackedWidget->setCurrentWidget(ui->P_CheckBoxDef);
        }
   }
   else{

    }
}

void StowPackages::ValidCheckedboxdef()
{

    QList<QListWidgetItem*> listitem;

    m_listBoxdeftmp.clear();
    m_listBoxtmp.clear();

    //si listbox empty message alerte

    for(int i=0;i<ui->listBOX_checkDef->count();i++)
    {
        //recupere les items
         listitem << ui->listBOX_checkDef->item(i);
    }

    for(int i=0;i< listitem.size();i++)
    {
        if(listitem[i]->checkState() == Qt::Checked)
        {
            //recupere les numeros des portes ckecked def
            m_listBoxdeftmp <<  listitem[i]->text().remove("Porte : ").toInt();
        }
        else{
            //recupere les numeros des portes qui n'ont pas de defaut
            m_listBoxtmp<< listitem[i]->text().remove("Porte : ").toInt();
        }
    }

    //affiche les portes
    qDebug()<<"ListPortedef:"<<m_listBoxdeftmp;
    qDebug()<<"ListPortechange"<<m_listBoxtmp;


    //mettre les portes qui ont un defaut en non disponible
    for(int i=0;i < m_listBoxdeftmp.size();i++)
    {        
        m_WBoxChoice->manageDoorUnvailable((m_listBoxdeftmp[i]-1));
    }

    //déselectionne les portes qui sont selectionne
    for(int i=0;i < m_listBoxtmp.size();i++)
    {
        m_WBoxChoice->manageRect((m_listBoxtmp[i]-1));
    }
    int nbox;
    nbox = m_listBoxdeftmp.size() + m_listBoxtmp.size();
    ui->label_selectionbox->setText(QString(QString(tr("Veuillez s&eacute;lectionner ").toUtf8()) + QString::number(nbox) + QString(tr(" consigne(s)").toUtf8())));
    ui->stackedWidget->setCurrentWidget(ui->P_changebox);

}

void StowPackages::CreateListBoxTreeWidget()
{
    for(int i = 0 ; i <m_listBox.size();i++)
    {
        CustomPushButton *buttonOpen;
        buttonOpen = new CustomPushButton(m_listBox[i],tr("OUVRIR"));
        connect(buttonOpen,SIGNAL(clicked(int)),this,SLOT(OpenDoor(int)));

        m_CustomTreeWidget->AddItem(m_listBox[i],buttonOpen);
    }

    //deverrouiller les portes concernées
    if(m_CDoors->UnlockDoors(m_listBox))
    {
        m_CDoors->OpenDoors(m_listBox);
        qDebug()<<"ouverture des portes";

        m_T_StatusDoors->setListBox(m_listBox);
        qDebug()<<"modification liste des portes";

        m_T_StatusDoors->start();
        qDebug()<<"demarrer thread";
    }
}

void StowPackages::OpenDoor(int door)
{
    QList<int> Ldoor;
    Ldoor << door;

    if(m_CDoors->UnlockDoors(Ldoor))
    {
        m_CDoors->OpenDoors(Ldoor);
    }
}

void StowPackages::StoragePackagesFinised()
{
    if(m_CustomTreeWidget->isDoorsClose(m_listBox))
    {
       m_T_StatusDoors->stopThread();
       m_T_StatusDoors->wait(1000);
       for(int i = 0 ; i<m_listBox.size();i++)
       {
           if(m_listBox[i] != m_listPackageBox[i].BoxNumber)
               m_listPackageBox[i].BoxNumber = m_listBox[i];
       }
       //envoi la liste des n°colis
       emit SendListPackageBox(m_listPackageBox);
       ShowDeliveryConfirm();
    }
    else{
        //message alerte
        int x;
        int y;
        x =  mapToGlobal(ui->B_Assistance->pos()).x()-ui->B_Assistance->width()-180;
        y =  mapToGlobal(ui->B_Assistance->pos()).y()-10;
        QToolTip::showText(QPoint(x,y),tr("Attention!!!<br/> Les portes ne sont pas ferm&eacute;es."),this);
    }


}

void StowPackages::SaveBoxSelected()
{
    QList<int> listbox;
    int x;
    int y;


    listbox = m_WBoxChoice->GetBoxSelected();

    qDebug()<<"listbox :"<<listbox;
    qDebug()<<"m_listbox :"<<m_listBox;

    x = mapToGlobal(ui->B_Assistance->pos()).x()-ui->B_Assistance->width()-180;
    y =  mapToGlobal(ui->B_Assistance->pos()).y()-10;

    if(listbox.isEmpty())
    {
        //message erreur aucune consigne selectionné

        QToolTip::showText(QPoint(x,y),tr("Attention!!!<br/> Vous n'avez pas s&eacute;lectionn&eacute; de consigne."),this);
    }
    else{

        m_T_StatusDoors->stopThread();
        m_T_StatusDoors->wait(1000);
        ui->treeWidget->clear();
        m_CustomTreeWidget->ClearListItem();

        if(listbox.size() == m_listBox.size())
        {

            for(int i = 0; i < m_listBox.size();i++)
            {
                if(listbox[i] != m_listBox[i])
                {

                    //replace le numero de la porte deselectionné par le nouveau numero de porte selectionné
                    m_listBox[i]=listbox[i];
                    qDebug()<<"replace ";

                }
            }
            UpdateBD();
            CreateListBoxTreeWidget();
            ShowStowP();
        }
        else{
             QToolTip::showText(QPoint(x,y),tr("Attention!!!<br/> Vous n'avez pas le m&ecirc;me nombre de consigne."),this);
        }
    }
}

void StowPackages::UpdateBD()
{
    if(!m_listBoxdeftmp.isEmpty())
    {
           m_BD->SetDammagedBoxes(m_listBoxdeftmp);
    }
}

void StowPackages::retranslateUi()
{
    ui->retranslateUi(this);
}
