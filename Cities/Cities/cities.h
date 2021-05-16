#ifndef CITIES_H
#define CITIES_H

#include <QMainWindow>
#include <QLocale>
#include <QChar>
#include <QPainter>
#include <QGraphicsScene>
#include <moveitem.h>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
namespace Ui { class cities; }
QT_END_NAMESPACE

class cities : public QMainWindow
{
    Q_OBJECT

public:
    cities(QWidget *parent = nullptr);
    ~cities();
    int a[16] [16], matrix[16][16],way[16][3],a2[16] [16], matrix2[16][16];
    int way_1[17];
    int tabl[16];
    int n,n2;
    int length;
    int start;
    int OperatNumber;
    bool flanguage;
    QLocale *loc=new QLocale(QLocale::English);
    int cordinates[16][3]={{0,0,0},
                         {0,280,270},
                            {0,280,420},
                          {0,530,520},
                          {0,610,620},
                            {0,220,630},
                            {0,60,640},
                            {0,200,730},
                          {0,380,560},
                           {0,190,510},
                          {0,460,320},
                           {0,500,190},
                           {0,660,380},
                            {0,700,740},
                           {0,820,460},
                           {0,750,570}};;

private slots:

    void on_bSelectCities_clicked();

    void on_bvvod_clicked();

    void function(int e);

    void reduction();

    void on_bCreateARoute_clicked();

    void on_bclear_clicked();

    void creatingitem(int i,int j,int a,bool color);

    void on_bChangeSize_clicked();

    void on_blanguage_clicked();

public slots:
    void pushNumButton();
private:
    Ui::cities *ui;
    QGraphicsScene *scene;
    QGraphicsTextItem *text;
};
#endif // CITIES_H

