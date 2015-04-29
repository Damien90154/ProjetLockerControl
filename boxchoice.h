#ifndef BOXCHOICE_H
#define BOXCHOICE_H


#include <QWidget>

#include "showwidgets.h"
#include <QGraphicsScene>
#include <QList>
#include "drawbox.h"
#include "DataStructures.h"
#include "menudelivery.h"
#include "csqlite_local_db.h"



namespace Ui {
class BoxChoice;
}

class BoxChoice : public QWidget
{
    Q_OBJECT

public:
    explicit BoxChoice(MenuDelivery *WMenuDelivery, CSQLite_Local_DB *, QWidget *parent = 0);
    void SetShowWidgets(ShowWidgets *TShowWidgets){m_ShowWidgets = TShowWidgets;}
    QGraphicsView* GetGraphicsView();
    QGraphicsScene* GetScene();
    ~BoxChoice();

    void retranslateUi();

    void manageDoorUnvailable(int id);
public slots:
    void ValidBox();
    void Cancel();
    void manageRect(int);
    void Refresh();
    QList<int> GetBoxSelected();

signals:
   void  SendListBoxSelected(QList<int>);

private:
    Ui::BoxChoice *ui;
    ShowWidgets *m_ShowWidgets;
    QGraphicsScene *m_Scene;
    MenuDelivery *m_WMenuDelivery;
    //lien base de donnée
    CSQLite_Local_DB *m_BD;

    QList<struct struct_DoorGeom> m_ListBox;
    QList<drawBox *> m_listdrawBox;

    void createBoxes();

};

#endif // BOXCHOICE_H
