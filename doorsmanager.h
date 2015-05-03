#ifndef DOORSMANAGER_H
#define DOORSMANAGER_H

#include <QWidget>
#include "csqlite_local_db.h"
#include "showwidgets.h"
#include "cdoors.h"
#include "boxchoice.h"

#define WINDEX_DOORS_MANAGER 0
#define WINDEX_DOORS_TEST 1
#define WINDEX_ADD_DEL_DOORS 2
#define WINDEX_ACT_DES_DOORS 3

namespace Ui {
class DoorsManager;
}

class DoorsManager : public QWidget
{
    Q_OBJECT

    public:
        explicit DoorsManager(QWidget *parent = 0, CSQLite_Local_DB *BD = NULL, CDoors *Doors = NULL,BoxChoice *WBoxChoice = NULL);
        void SetShowWidgets(ShowWidgets *TShowWidgets){m_ShowWidgets = TShowWidgets;}
        ~DoorsManager();

    public slots:
        void ReturnHome() {m_ShowWidgets->ShowWConsoleWindows();}
        void GotoDoorsManager();
        void GotoDoorsTest();
        void GotoAddDelDoors();
        void GotoActDesDoors();
        void SelectedBoxes();

    private:
        Ui::DoorsManager *ui;
        CSQLite_Local_DB *m_DB;
        CDoors *m_Doors;
        ShowWidgets *m_ShowWidgets;
        BoxChoice *m_BoxesSelector;
};

#endif // DOORSMANAGER_H
