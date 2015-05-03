#include "doorsmanager.h"
#include "ui_doorsmanager.h"
#include "DataStructures.h"

#include <QDebug>

DoorsManager::DoorsManager(QWidget *parent, CSQLite_Local_DB *BD, CDoors *Doors, BoxChoice *WBoxChoice) :
    QWidget(parent),
    ui(new Ui::DoorsManager)
{
    ui->setupUi(this);
    if( (BD != NULL) && (Doors != NULL) && (WBoxChoice != NULL) )
    {
        m_DB = BD;
        m_Doors = Doors;
        m_BoxesSelector = WBoxChoice;

        ui->SelectDoors_GraphicsView->setScene(m_BoxesSelector->GetScene());

        connect(ui->B_Home,SIGNAL(clicked()), this,SLOT(ReturnHome()));
        connect(ui->B_Home_2,SIGNAL(clicked()), this,SLOT(ReturnHome()));
        connect(ui->B_Home_3,SIGNAL(clicked()), this,SLOT(ReturnHome()));
        connect(ui->B_Home_4,SIGNAL(clicked()), this,SLOT(ReturnHome()));
        connect(ui->B_ValidBoxesSelect,SIGNAL(clicked()), this,SLOT(SelectedBoxes()));
        connect(ui->B_DoorTest,SIGNAL(clicked()), this,SLOT(GotoDoorsTest()));
        connect(ui->B_AddDel_Door,SIGNAL(clicked()), this,SLOT(GotoAddDelDoors()));
        connect(ui->B_ActDes_Door,SIGNAL(clicked()), this,SLOT(GotoActDesDoors()));
    }
    else
        qDebug() << "[FATAL ERROR] : Uninitiatized pointer on object";
}

void DoorsManager::GotoDoorsManager()
{
    ui->stackedWidget_DoorsManager->setCurrentIndex(WINDEX_DOORS_MANAGER);
}

void DoorsManager::GotoDoorsTest()
{
    ui->stackedWidget_DoorsManager->setCurrentIndex(WINDEX_DOORS_TEST);
}

void DoorsManager::GotoAddDelDoors()
{
    ui->stackedWidget_DoorsManager->setCurrentIndex(WINDEX_ADD_DEL_DOORS);
}

void DoorsManager::GotoActDesDoors()
{
    ui->stackedWidget_DoorsManager->setCurrentIndex(WINDEX_ACT_DES_DOORS);
}

void DoorsManager::SelectedBoxes()
{
    QList<int> SelectedBoxesList;
    QList<struct struct_DoorsStatus> DoorsStatusList;

    SelectedBoxesList.append(m_BoxesSelector->GetBoxSelected());
    DoorsStatusList.append(m_Doors->DoorsStatus(SelectedBoxesList));

    for(int i=0; i<DoorsStatusList.count(); i++)
    {

    }
}

DoorsManager::~DoorsManager()
{
    delete ui;
}
