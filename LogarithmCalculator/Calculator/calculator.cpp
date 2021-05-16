#include "calculator.h"
#include "ui_calculator.h"

calculator::calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::calculator)
{
    ui->setupUi(this);
    ui->tablo_1->setText("0");
    dot=false;
    op=false;
    x=0;
    y=0;
    lg=NULL;
    trans=false;
    flanguage=true;
    operationXY=EMPTY;
    setWindowTitle("Logarithm calculator");
    connect (ui->b0,SIGNAL(clicked(bool)),this,SLOT(pushNumButton()));
    connect (ui->b00,SIGNAL(clicked(bool)),this,SLOT(pushNumButton()));
    connect (ui->b1,SIGNAL(clicked(bool)),this,SLOT(pushNumButton()));
    connect (ui->b2,SIGNAL(clicked(bool)),this,SLOT(pushNumButton()));
    connect (ui->b3,SIGNAL(clicked(bool)),this,SLOT(pushNumButton()));
    connect (ui->b4,SIGNAL(clicked(bool)),this,SLOT(pushNumButton()));
    connect (ui->b5,SIGNAL(clicked(bool)),this,SLOT(pushNumButton()));
    connect (ui->b6,SIGNAL(clicked(bool)),this,SLOT(pushNumButton()));
    connect (ui->b7,SIGNAL(clicked(bool)),this,SLOT(pushNumButton()));
    connect (ui->b8,SIGNAL(clicked(bool)),this,SLOT(pushNumButton()));
    connect (ui->b9,SIGNAL(clicked(bool)),this,SLOT(pushNumButton()));
    connect(ui->bPlus,SIGNAL(clicked(bool)),this,SLOT(pushOperationButton()));
    connect(ui->bMinus,SIGNAL(clicked(bool)),this,SLOT(pushOperationButton()));
    connect(ui->bMultiply,SIGNAL(clicked(bool)),this,SLOT(pushOperationButton()));
    connect(ui->bDivision,SIGNAL(clicked(bool)),this,SLOT(pushOperationButton()));
    connect(ui->bDegree,SIGNAL(clicked(bool)),this,SLOT(pushOperationButton()));
    connect(ui->bRoot,SIGNAL(clicked(bool)),this,SLOT(pushOperationButton()));
    connect(ui->btransion,SIGNAL(clicked(bool)),this,SLOT(pushOperationButton()));

}

calculator::~calculator()
{
    delete ui;
}

void calculator::pushNumButton()//ввод чисел
{
    QPushButton*tempButton=(QPushButton*)sender();
    QString sDigit=tempButton->text();


    if(op==false)
    {
        if (ui->tablo_1->text()=="0" && flagx==false)
        {
            ui->tablo_1->setText(sDigit);
        }
        else if(flagx==false)
        {
            ui->tablo_1->setText(ui->tablo_1->text()+sDigit);
        }
        else
        {
            if(flanguage==true) ui->tablo_error->setText("Error: enter operation!!!");
            else ui->tablo_error->setText("Ошибка: введите операцию!!!");
        }
    }
    else
    {
        if (ui->tablo_3->text()=="0")
        {
            ui->tablo_3->setText(sDigit);
        }
        else
        {
            ui->tablo_3->setText(ui->tablo_3->text()+sDigit);
        }
    }

}




void calculator::pushOperationButton()//ввод основных операции и вычисление
{
    ui->tablo_error->setText("");
    operation tekOp=EMPTY;
    fa=false,fb=false;
    if(sender()->objectName()=="bPlus")
    {
        tekOp=PLUS;
        ui->tablo_2->setText("+");
        trans=false;
    }
    if(sender()->objectName()=="bMinus")
    {
        tekOp=MINUS;
        ui->tablo_2->setText("-");
        trans=false;
    }
    if(sender()->objectName()=="bMultiply")
    {
        tekOp=MULTIPLY;
        ui->tablo_2->setText("*");
        trans=false;
    }
    if(sender()->objectName()=="bDivision")
    {
        tekOp=DIVISION;
        ui->tablo_2->setText("/");
        trans=false;
    }
    if(sender()->objectName()=="bDegree")
    {
        tekOp=DEGREE;
        ui->tablo_2->setText("^");
        trans=false;
    }
    if(sender()->objectName()=="bRoot")
    {
        tekOp=ROOT;
        ui->tablo_2->setText("√");
        trans=false;
    }
    if(sender()->objectName()=="btransion" &&trans==true&& F_log1==true)//&& F_log1==true
    {
        tekOp=TRANSION;
        ui->tablo_2->setText("→");
    }
    else if (sender()->objectName()=="btransion")// && trans==false)
    {
        if(flanguage==true) ui->tablo_error->setText("Error: the -> sign is only used in logarithm");
        else ui->tablo_error->setText("Ошибка: знак -> используется только в логарифмах!!!");
        ui->tablo_2->setText("");
    }
    if(operationXY==EMPTY)
    {
        x=loc->toDouble(ui->tablo_1->text());
        dot=false;
        operationXY=tekOp;
        op=true;
    }
    else
    {
        if (F_log1==true && FL1==false)
        {
           st=ui->tablo_1->text();
           FL1=true;
           QString a, b;
           double a1=0, a2=0;
           for (auto c : st)
           {
               if (c == ')') a1 = 2;
               if (c == ')'&& a1==2) a2 = 2;
               if (a1 == 1) a = a + c;
               if (a2 == 1) b = b + c;
               if (c == '(' && a1==0) a1 = 1;
               if (c == '(' && a1==2) a2 = 1;
           }
           double x1=0,x2=0;
           x1=loc->toDouble(b);
           if(x1<=0)
           {
               fb=true;
           }
           lg=x1;
           if (x1>0)
           {
               x2=loc->toDouble(a);
               if(x2<=0 ||x2==1)
               {
                   fa=true;
               }
               if(x2!=1 && x2>0)
               {
                   x=log(x1)/log(x2);
               }
           }
        }
        y=loc->toDouble(ui->tablo_3->text());
        if (F_log2==true )
        {
            st=ui->tablo_3->text();
            QString a, b;
            double a1=0, a2=0;
            for (auto c : st)
            {
                if (c == ')') a1 = 2;
                if (c == ')'&& a1==2) a2 = 2;
                if (a1 == 1) a = a + c;
                if (a2 == 1) b = b + c;
                if (c == '(' && a1==0) a1 = 1;
                if (c == '(' && a1==2) a2 = 1;
            }
            double x1=0,x2=0;
            x1=loc->toDouble(b);
            if(x1<=0)
            {
                fb=true;
            }
            if (x1>0)
            {
                x2=loc->toDouble(a);
                if(x2<=0 ||x2==1)
                {
                    fa=true;
                }
                if(x2!=1 && x2>0)
                {
                    y=log(x1)/log(x2);
                }
            }
        }
        if (fa==true)
        {
            if(flanguage==true) ui->tablo_error->setText("Error: the base of the logarithm must be >0 and not = 1!!!");
            else ui->tablo_error->setText("Ошибка: основание логарифма должно быть >0 и не = 1!!!");
        }
        else if(fb==true)
        {
            if(flanguage==true) ui->tablo_error->setText("Error: The argument of the logarithm expression must be >0!!!");
            else ui->tablo_error->setText("Ошибка: подлогарифмическое выражение должно быть >0!!!");
        }
        else
        {
        if (operationXY==PLUS) x=x+y;
        if (operationXY==MINUS) x=x-y;
        if (operationXY==MULTIPLY) x=x*y;
        if (operationXY==DIVISION)
        {
            if (y!=0)
            {
                x=x/y;
            }
            else
            {
                if(flanguage==true) ui->tablo_error->setText("Error: you can't divide by 0!!!");
                else ui->tablo_error->setText("Ошибка: на 0 делить нельзя!!!");
            }
        }
        if (operationXY==DEGREE) x=pow(x,y);
        if (operationXY==ROOT)
        {
            if (x>0)
            {
                x=pow(x,1/y);
            }
            else
            {
                if(flanguage==true) ui->tablo_error->setText("Error: the radical expression must be >0!!!");
                else ui->tablo_error->setText("Ошибка: подкоренное выражение должно быть >0!!!");
            }
        }
        if (operationXY==TRANSION)
        {
            ui->tablo_1->setText("log(");
            ui->tablo_1->setText(ui->tablo_1->text()+(loc->toString((y))));
            ui->tablo_1->setText(ui->tablo_1->text()+")(");
            ui->tablo_1->setText(ui->tablo_1->text()+loc->toString((lg)));
            ui->tablo_1->setText(ui->tablo_1->text()+")");
            FL1=false;
        }
        else
        {
            ui->tablo_1->setText((loc->toString((x))));
            trans=false;
        }
        ui->tablo_3->setText("0");
        dot=false;
        operationXY=tekOp;
        op=true;
        flagx=true;
        F_log2=false;
        }
    }
}



void calculator::on_bResult_clicked()//результат (знак "=")
{
    fa=false,fb=false;
    if (F_log1==true && FL1==false)
    {
       st=ui->tablo_1->text();
       FL1=true;
       QString a, b;
       double a1=0, a2=0;
       for (auto c : st)
       {
           if (c == ')') a1 = 2;
           if (c == ')'&& a1==2) a2 = 2;
           if (a1 == 1) a = a + c;
           if (a2 == 1) b = b + c;
           if (c == '(' && a1==0) a1 = 1;
           if (c == '(' && a1==2) a2 = 1;
       }
       double x1=0,x2=0;
       x1=loc->toDouble(b);
       if(x1<=0)
       {
           fb=true;
       }
       lg=x1;
       if (x1>0)
       {
           x2=loc->toDouble(a);
           if(x2<=0 ||x2==1)
           {
               fa=true;
           }
           if(x2!=1 && x2>0)
           {
               x=log(x1)/log(x2);
           }
       }
    }
    y=loc->toDouble(ui->tablo_3->text());
    if (F_log2==true )
    {
        st=ui->tablo_3->text();
        QString a, b;
        double a1=0, a2=0;
        for (auto c : st)
        {
            if (c == ')') a1 = 2;
            if (c == ')'&& a1==2) a2 = 2;
            if (a1 == 1) a = a + c;
            if (a2 == 1) b = b + c;
            if (c == '(' && a1==0) a1 = 1;
            if (c == '(' && a1==2) a2 = 1;
        }
        double x1=0,x2=0;
        x1=loc->toDouble(b);
        if(x1<=0)
        {
            fb=true;
        }
        if (x1>0)
        {
            x2=loc->toDouble(a);
            if(x2<=0 ||x2==1)
            {
                fa=true;
            }
            if(x2!=1 && x2>0)
            {
                y=log(x1)/log(x2);
            }
        }
    }
    if (fa==true)
    {
        if(flanguage==true) ui->tablo_error->setText("Error: the base of the logarithm must be >0 and not = 1!!!");
        else ui->tablo_error->setText("Ошибка: основание логарифма должно быть >0 и не = 1!!!");
    }
    else if(fb==true)
    {
        if(flanguage==true) ui->tablo_error->setText("Error: The argument of the logarithm expression must be >0!!!");
        else ui->tablo_error->setText("Ошибка: подлогарифмическое выражение должно быть >0!!!");
    }
    else
    {
    if (operationXY==PLUS) x=x+y;
    if (operationXY==MINUS) x=x-y;
    if (operationXY==MULTIPLY) x=x*y;
    if (operationXY==DIVISION)
    {
        if (y!=0)
        {
            x=x/y;
        }
        else
        {
            if(flanguage==true) ui->tablo_error->setText("Error: you can't divide by 0!!!");
            else ui->tablo_error->setText("Ошибка: на 0 делить нельзя!!!");
        }
    }
    if (operationXY==DEGREE) x=pow(x,y);
    if (operationXY==ROOT)
    {
        if (x>0)
        {
            x=pow(x,1/y);
        }
        else
        {
            if(flanguage==true) ui->tablo_error->setText("Error: the radical expression must be >0!!!");
            else ui->tablo_error->setText("Ошибка: подкоренное выражение должно быть >0!!!");
        }
    }
    if (operationXY==TRANSION)
    {
        ui->tablo_1->setText("log(");
        ui->tablo_1->setText(ui->tablo_1->text()+(loc->toString((y))));
        ui->tablo_1->setText(ui->tablo_1->text()+")(");
        ui->tablo_1->setText(ui->tablo_1->text()+loc->toString((lg)));
        ui->tablo_1->setText(ui->tablo_1->text()+")");
        FL1=false;
    }
    else
    {
        ui->tablo_1->setText((loc->toString((x))));
        trans=false;
    }
    ui->tablo_2->setText(" ");
    ui->tablo_3->setText("0");
    op=false;
    flagx=true;
    F_log2=false;
    operationXY=EMPTY;
    }
}



void calculator::on_bClear_clicked()// очистка всех полей
{
    op=false;
    dot=0;
    x=0;
    y=0;
    operationXY=EMPTY;
    ui->tablo_1->setText("0");
    ui->tablo_2->setText(" ");
    ui->tablo_3->setText("0");
    ui->tablo_error->setText("");
    flagx=false;
    F_log1=false;
    F_log2=false;
    FL1=false;
}

void calculator::on_bDEL_clicked() //удаление последнего элемента
{
    if (op==false&&flagx==false)
    {
       st=ui->tablo_1->text();
       st.chop(1);
       ui->tablo_1->setText(st);
    }
    else
    {
        st=ui->tablo_3->text();
        st.chop(1);
        ui->tablo_3->setText(st);
    }

}




void calculator::on_bDot_clicked() // добавляет "."
{
    if (op==false)
    {
        if (!dot && flagx==false)
        {
                ui->tablo_1->setText(ui->tablo_1->text()+".");
                dot=true;
        }
    }
    else
    {
        if (!dot)
        {
                ui->tablo_3->setText(ui->tablo_3->text()+".");
                dot=true;
        }
    }

}



void calculator::on_bSign_clicked() //меняет знак
{
    if (op==false)
    {
        double temp=loc->toDouble(ui->tablo_1->text());
        temp=-temp;
        ui->tablo_1->setText(loc->toString(temp));
    }
    else
    {
        double temp=loc->toDouble(ui->tablo_3->text());
        temp=-temp;
        ui->tablo_3->setText(loc->toString(temp));
    }
}


void calculator::on_bdivision_clicked() //деление 1 на число
{
    if (op==false)
    {
        double temp=loc->toDouble(ui->tablo_1->text());
        if (temp!=0)
        {
            temp=1/temp;
            ui->tablo_1->setText(loc->toString(temp));
        }
        else
        {
            if(flanguage==true) ui->tablo_error->setText("Error: you can't divide by 0!!!");
            else ui->tablo_error->setText("Ошибка: на 0 делить нельзя!!!");
        }
    }
    else
    {
        double temp=loc->toDouble(ui->tablo_3->text());
        if (temp!=0)
        {
            temp=1/temp;
            ui->tablo_3->setText(loc->toString(temp));
        }
        else
        {
            if(flanguage==true) ui->tablo_error->setText("Error: you can't divide by 0!!!");
            else ui->tablo_error->setText("Ошибка: на 0 делить нельзя!!!");
        }
    }
}


void calculator::on_bLog_clicked() // добавление логарифма
{
    if (op==false )
    {
        if(flagx==false)
        {
            ui->tablo_1->setText("log()()");
            F_log1=true;
            trans=true;
        }
        else
        {
            if(flanguage==true) ui->tablo_error->setText("Error: enter operation!!!");
            else ui->tablo_error->setText("Ошибка: введите операцию!!!");
        }
    }
    else
    {
        ui->tablo_3->setText("log()()");
        F_log2=true;
    }
}







void calculator::on_bl_clicked() //добавление знака "("
{
    if (op==false &&F_log1==true)
    {
        if (flagx==false)
        {
            ui->tablo_1->setText(ui->tablo_1->text()+"(");
        }
        else
        {
            if(flanguage==true) ui->tablo_error->setText("Error: The characters' ('and') ' are only used in logarithms!!!");
            else ui->tablo_error->setText("Ошибка: знаки '(' и ')' используются только в логарифмах!!!");
        }
    }
    else
    {
        if (F_log2==true)
        {
            ui->tablo_3->setText(ui->tablo_3->text()+"(");
        }
        else
        {
            if(flanguage==true) ui->tablo_error->setText("Error: The characters' ('and') ' are only used in logarithms!!!");
            else ui->tablo_error->setText("Ошибка: знаки '(' и ')' используются только в логарифмах!!!");
        }
    }

}



void calculator::on_br_clicked() //добавление знака ")"
{
    if (op==false &&F_log1==true)
    {
        if (flagx==false)
        {
            ui->tablo_1->setText(ui->tablo_1->text()+")");
        }
        else
        {
            if(flanguage==true) ui->tablo_error->setText("Error: The characters' ('and') ' are only used in logarithms!!!");
            else ui->tablo_error->setText("Ошибка: знаки '(' и ')' используются только в логарифмах!!!");
        }
    }
    else
    {
        if (F_log2==true)
        {
            ui->tablo_3->setText(ui->tablo_3->text()+")");
        }
        else
        {
            if(flanguage==true) ui->tablo_error->setText("Error: The characters' ('and') ' are only used in logarithms!!!");
            else ui->tablo_error->setText("Ошибка: знаки '(' и ')' используются только в логарифмах!!!");
        }
    }


}


void calculator::on_blanguage_clicked()//язык
{
    if(flanguage==true)
    {
        ui->blanguage->setText("РУС");
        flanguage=false;
    }
    else
    {
        ui->blanguage->setText("ENG");
        flanguage=true;
    }
}
