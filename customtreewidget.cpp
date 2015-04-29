#include "customtreewidget.h"
#include <QHeaderView>

#define C_DOORSNUMBERS   0
#define C_STATUSOFDOORS  1
#define C_REOPENINGDOORS 2

CustomTreeWidget::CustomTreeWidget(QTreeWidget *treewidget)
{
    m_TreeWidget = treewidget;
    m_TreeWidget->header()->setMovable(false);
    m_TreeWidget->header()->setDragEnabled(false);
}

void CustomTreeWidget::AddItem(int numberbox , CustomPushButton *button)
{
    //creation de l'item
    QTreeWidgetItem *item = new QTreeWidgetItem();

    item->setText(0,QString::number(numberbox));

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight);
    layout->addWidget(button,0,Qt::AlignCenter);

    QWidget *widget = new QWidget();
    widget->setLayout(layout);
    widget->setStyleSheet("background:transparent");
    button->setDisabledB(true);

    //ajout de l'item
    m_TreeWidget->addTopLevelItem(item);
    m_TreeWidget->setItemWidget(item,C_REOPENINGDOORS,widget);

    m_listItemTreeWidget << item;
    m_listButtonOpen << button;

}

void CustomTreeWidget::EditedItem_ColumnStatusOfDoor(int numberbox, QString textedited, QColor color)
{
    int index;

    index = getIndexListItem(numberbox);

    m_listItemTreeWidget[index]->setTextAlignment(C_STATUSOFDOORS,Qt::AlignCenter);
    m_listItemTreeWidget[index]->setText(C_STATUSOFDOORS,textedited);
    m_listItemTreeWidget[index]->setTextColor(C_STATUSOFDOORS,color);

}


void CustomTreeWidget::ButtonVisible(int numberbox,bool status)
{
    int index;

    index = getIndexListItem(numberbox);
    m_listButtonOpen[index]->setDisabledB(status);

}

int CustomTreeWidget::getIndexListItem(int numberbox)
{
    int index;

    for(int i = 0 ; i < m_listItemTreeWidget.size() ; i++)
    {
        if(m_listItemTreeWidget[i]->text(C_DOORSNUMBERS).toInt() == numberbox)
        {
            index = i;
        }
    }

    return index;
}

void CustomTreeWidget::ClearListItem()
{
    m_listItemTreeWidget.clear();
    m_listButtonOpen.clear();
}

bool CustomTreeWidget::isDoorsClose(QList<int> listbox)
{
    bool result = true;
    QList<bool> liststatus;
    QString close = QObject::tr("FERME");

    for(int i = 0 ; i < listbox.size(); i++)
    {
        int index;

        index = getIndexListItem(listbox[i]);
        if(m_listItemTreeWidget[index]->text(C_STATUSOFDOORS).compare(close) == 0)
        {
            liststatus << true;
        }
        else{
            liststatus << false;
        }

    }

    int i = 0;
    while (i < liststatus.size()) {
        if(liststatus[i] == false)
        {
            result = false;
        }
        i++;
    }

    return result;
}

