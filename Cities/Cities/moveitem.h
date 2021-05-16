#ifndef MOVEITEM_H
#define MOVEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

class MoveItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
  int cordinat[16][3];
  bool color;
    int i;int j,a;
        void Init(int, int,int,int[16][3],bool);

    explicit MoveItem(QObject *parent = 0);
    ~MoveItem();

QLocale *loc=new QLocale(QLocale::English);
signals:

private:
    QRectF boundingRect() const;
    void paint(QPainter *painte, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QGraphicsTextItem *text;

public slots:
};

#endif // MOVEITEM_H

