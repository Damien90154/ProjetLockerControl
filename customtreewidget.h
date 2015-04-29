#ifndef CUSTOMTREEWIDGET_H
#define CUSTOMTREEWIDGET_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "custompushbutton.h"

class CustomTreeWidget
{
    public:
        CustomTreeWidget(QTreeWidget *treewidget);
        ~CustomTreeWidget();

        void AddItem(int numberbox, CustomPushButton *button);
        void EditedItem_ColumnStatusOfDoor(int numberbox ,QString textedited , QColor color);
        void ButtonVisible(int numberbox, bool);
        void ClearListItem();

        bool isDoorsClose(QList<int> listbox);        

private :
        int getIndexListItem(int numberbox);
        QTreeWidget *m_TreeWidget;
        QList<QTreeWidgetItem *> m_listItemTreeWidget;
        QList<CustomPushButton * > m_listButtonOpen;

};

#endif // CUSTOMTREEWIDGET_H
