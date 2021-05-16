#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QLocale>
#include <QChar>

QT_BEGIN_NAMESPACE
namespace Ui { class calculator; }
QT_END_NAMESPACE

class calculator : public QMainWindow
{
    Q_OBJECT

public:
    calculator(QWidget *parent = nullptr);
    ~calculator();
private:
    double x,y,lg;
    enum operation {EMPTY,PLUS,MINUS,MULTIPLY,DIVISION,DEGREE,ROOT,TRANSION};
    operation operationXY;
    bool dot=false;
    bool op=false;
    bool flagx=false;
    bool F_log1=false;
    bool FL1=false;
    bool F_log2=false;
    bool trans=false;
    double mult=0;
    bool fa=false,fb=false;
    bool flanguage=true;
    QString st;
    QLocale *loc=new QLocale(QLocale::English);

public slots:
    void pushNumButton();
    void pushOperationButton();

private slots:
    void on_bResult_clicked();

    void on_bClear_clicked();

    void on_bDEL_clicked();

    void on_bDot_clicked();

    void on_bSign_clicked();

    void on_bdivision_clicked();

    void on_bLog_clicked();

    void on_bl_clicked();

    void on_br_clicked();

    void on_blanguage_clicked();

private:
    Ui::calculator *ui;
};
#endif // CALCULATOR_H
