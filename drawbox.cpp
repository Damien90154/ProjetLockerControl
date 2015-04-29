#include "drawbox.h"

#include <QDebug>
#include <QBrush>
#include <QColor>
#include "DataStructures.h"
#include <QTextItem>


drawBox::drawBox(int id, QGraphicsItem * parent ) :
   QObject(), QGraphicsRectItem(parent)
{
    m_IdRect = id;
    m_porte = QString::number(m_IdRect);

    this->setAcceptedMouseButtons(Qt::LeftButton);
}

drawBox::~drawBox()
{
}


void drawBox::mousePressEvent ( QGraphicsSceneMouseEvent  * event )
{

    emit MyId(m_IdRect);

    QGraphicsRectItem::mousePressEvent(event);
}

void drawBox::drawRect(int x, int y, int width, int height)
{
    QPen pen;
        pen.setColor(Qt::black);
        pen.setWidth(2);
    setRect( x , y , width, height);

    setPen(pen);


}


void drawBox::setColor(int status)
{
    QColor couleur;

    switch (status)
    {
        case  OK :
            couleur = Qt::green;
            break;
        case  KO :
            couleur = Qt::red;
            break;
        case  SELECTED :
            couleur = Qt::cyan;
            break;

        default :
        break;
    }
    setBrush( QBrush(couleur));
}
