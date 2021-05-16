#include "moveitem.h"
#include <QGraphicsTextItem>

void MoveItem::Init(int F, int S,int A,int cor[16][3],bool cl)
{
    i=F;
    j=S;
    a=A;
    for (int q=0;q<16;q++)
    {
        for(int p=0;p<3;p++)
        {
            cordinat[q][p]=cor[q][p];
        }
    }
    color=cl;
}

MoveItem::MoveItem(QObject *parent) :
    QObject(parent), QGraphicsItem()
{

}

MoveItem::~MoveItem()
{

}

QRectF MoveItem::boundingRect() const
{
    return QRectF (-30,-30,1100,820);
}

void MoveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (color)
    {
        painter->setPen(QPen (Qt::red, 3, Qt::SolidLine));
    }
    else painter->setPen(QPen (Qt::yellow, 3, Qt::SolidLine));
  painter->drawLine(cordinat[i][1]+5,cordinat[i][2]+15, cordinat[j][1]+5, cordinat[j][2]+15);

        Q_UNUSED(option);
    Q_UNUSED(widget);
}
