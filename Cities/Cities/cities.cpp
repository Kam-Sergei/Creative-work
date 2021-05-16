#include "cities.h"
#include "ui_cities.h"
#include <QGraphicsTextItem>

cities::cities(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cities)
{
    ui->setupUi(this);
    ui->tablo_1->setText("");
    for(int i=1;i<=15;i++)
    {
        for(int j=1;j<=15;j++)
        {
        a[i] [j] =matrix[i][j]=-1;
        }
    }
    for (int i=0;i<=15;i++)
    {
        a[0][i] =matrix[0][i]=i;
        a[i][0] =matrix[i][0]=i;
    }
    OperatNumber=0;
    n=0;
    start=1;
    scene = new QGraphicsScene(this);   // Инициализируем графическую сцену
    scene->setItemIndexMethod(QGraphicsScene::NoIndex); // настраиваем индексацию элементов
    ui->graphicsView->resize(1100,820);  // Устанавливаем размер graphicsView
    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Настраиваем рендер
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground); // Кэш фона
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    scene->setSceneRect(0,0,1100,815); // Устанавливаем размер сцены

    flanguage=true;
    ui->l1->setText("Saint-Petersburg");
    ui->l2->setText("Moscow");
    ui->l3->setText("Perm");
    ui->l4->setText("Tyumen");
    ui->l5->setText("Volgograd");
    ui->l6->setText("Sochi");
    ui->l7->setText("Astrakhan");
    ui->l8->setText("Kazan");
    ui->l9->setText("Voronezh");
    ui->l10->setText("Arkhangelsk");
    ui->l11->setText("Murmansk");
    ui->l12->setText("Vorkuta");
    ui->l13->setText("Omsk");
    ui->l14->setText("New Urengoy");
    ui->l15->setText("Surgut");
    ui->bvvod->setText("Enter");
    ui->bSelectCities->setText("Set cities");
    ui->bChangeSize->setText("Change the road size");
    ui->bCreateARoute->setText("Create a route");
    ui->bclear->setText("Clear");


    connect (ui->b1,SIGNAL(clicked(bool)),this,SLOT(pushNumButton()));
    connect (ui->b2,SIGNAL(clicked(bool)),this,SLOT(pushNumButton()));
    connect (ui->b3,SIGNAL(clicked(bool)),this,SLOT(pushNumButton()));
    connect (ui->b4,SIGNAL(clicked(bool)),this,SLOT(pushNumButton()));
    connect (ui->b5,SIGNAL(clicked(bool)),this,SLOT(pushNumButton()));
    connect (ui->b6,SIGNAL(clicked(bool)),this,SLOT(pushNumButton()));
    connect (ui->b7,SIGNAL(clicked(bool)),this,SLOT(pushNumButton()));
    connect (ui->b8,SIGNAL(clicked(bool)),this,SLOT(pushNumButton()));
    connect (ui->b9,SIGNAL(clicked(bool)),this,SLOT(pushNumButton()));
    connect (ui->b10,SIGNAL(clicked(bool)),this,SLOT(pushNumButton()));
    connect (ui->b11,SIGNAL(clicked(bool)),this,SLOT(pushNumButton()));
    connect (ui->b12,SIGNAL(clicked(bool)),this,SLOT(pushNumButton()));
    connect (ui->b13,SIGNAL(clicked(bool)),this,SLOT(pushNumButton()));
    connect (ui->b14,SIGNAL(clicked(bool)),this,SLOT(pushNumButton()));
    connect (ui->b15,SIGNAL(clicked(bool)),this,SLOT(pushNumButton()));

}

cities::~cities()
{
    delete ui;
}

void cities::pushNumButton()//ввод чисел
{
    QPushButton*tempButton=(QPushButton*)sender();
    QString sDigit=tempButton->text();
    if (ui->tablo_1->text()=="" )
        {
            ui->tablo_1->setText(sDigit);
        }
        else
        {
            ui->tablo_1->setText(ui->tablo_1->text()+","+sDigit);
        }

}






void cities::creatingitem(int i,int j,int a,bool color)//рисование на сцене
{
    MoveItem *item = new MoveItem();        // Создаём графический элемента
    item->Init(i,j,a,cordinates,color);
    scene->addItem(item);

   QGraphicsTextItem *textItem = scene->addText(loc->toString(a));
       textItem->setPos((cordinates[i][1]+cordinates[j][1])/2,(cordinates[i][2]+cordinates[j][2])/2);
}

void cities::on_bSelectCities_clicked() //задать города
{
    if(flanguage==true) ui->tablo_vivod->setText("Enter the city numbers for the route (Example: 1,5,12,3)");
    else ui->tablo_vivod->setText("Введите номера городов для маршрута (Пример: 1,5,12,3)");
    OperatNumber=1;
}

void cities::on_bChangeSize_clicked() //поменять размер дороги
{
    if(flanguage==true) ui->tablo_vivod->setText("Enter two cities and a size (Example: 12,5,2345)");
    else ui->tablo_vivod->setText("Введите два города и размер (Пример: 12,5,2345)");
    OperatNumber=2;
}

void cities::on_bCreateARoute_clicked() //создать маршрут
{
    if(flanguage==true) ui->tablo_vivod->setText("Enter the starting city (Example: 7)");
    else ui->tablo_vivod->setText("Введите начальный город (Пример: 7)");
    OperatNumber=3;

}



void cities::function(int e) // вычисление самого большого 0 и присваивание его строке и столбцу -1
{
    int line, column , max = -1,minline,mincolumn;
        for (int i = 1; i <= n2; i++)
        {
            for (int j = 1; j <= n2; j++)
            {
                if (matrix2[i][j] == 0)  // ищем нулевой элемент
                {
                    line = -1;
                    column = -1;
                    for (int q = 1; q <= n2; q++)
                    {
                        if ((matrix2[i][q] < line || line== -1) && matrix2[i][q] != -1 && q != j)
                        {
                            line = matrix2[i][q];
                        }
                        if ((matrix2[q][j] < column ||column == -1) && matrix2[q][j] != -1 && q != i)
                        {
                            column = matrix2[q][j];
                        }
                    }
                    if (line == -1) line = 0;
                    if (column == -1) column = 0;
                    int t = line + column;// считаем сумму минимальных элементов в строке и столбце
                    if (t > max) {
                        max = t;
                        minline = i;
                        mincolumn = j;
                    }
                }
            }
        }
        // запись пути в массив путей
        way[e][1] = minline;
        way[e][2] = mincolumn;
        e++;
        matrix2[mincolumn][minline] = -1;
        for (int i = 1; i <= n2; i++)
        {
            matrix2[minline][i] = -1;
            matrix2[i][mincolumn] = -1;
        }
}

void cities::reduction() //редукция строк и столбцов
{
    int minline[21];// минимальные элементы в строках
        for (int i = 1; i <= n2; i++)
        {
            minline[i] = -1;
            for (int j = 1; j <= n2; j++)
            {
                if ((matrix2[i][j] < minline[i] || minline[i] == -1) && matrix2[i][j] != -1)
                {
                    minline[i] = matrix2[i][j];
                }
            }
            if (minline[i] == -1) minline[i] = 0;
        }
        for (int i = 1; i <= n2; i++)//вычитание минимального эл. строки из всей строки
        {
            for (int j = 1; j <= n2; j++)
            {
                if (matrix2[i][j] !=-1) matrix2[i][j] = matrix2[i][j] - minline[i];
            }
        }
        int mincolumn[16];// минимальные элементы в столбцах
        for (int i = 1; i <= n2; i++)
        {
            mincolumn[i] = -1;
            for (int j = 1; j <= n2; j++)
            {
                if ((matrix2[j][i] < mincolumn[i] || mincolumn[i] == -1) && matrix2[j][i] != -1)
                {
                    mincolumn[i] = matrix2[j][i];
                }
            }
            if (mincolumn[i] == -1) mincolumn[i] = 0;
        }
        for (int i = 1; i <= n2; i++)//вычитание минимального эл. стотлбца из всго столбца
        {
            for (int j = 1; j <= n2; j++)
            {
                if (matrix2[i][j] !=-1) matrix2[j][i] = matrix2[j][i] - mincolumn[i];
            }
        }
}





void cities::on_bvvod_clicked()// ввод
{
    if(OperatNumber==0)
    {
         if(flanguage==true) ui->tablo_vivod->setText("Error: enter the operation!!!");
         else ui->tablo_vivod->setText("Ошибка: введите операцию!!!");
    }
    if(OperatNumber==1)
    {
        srand(time(0)) ;
        QString st=ui->tablo_1->text();
        int CityNum[16];
        n=1;
        QString st1;
        for (auto c : st)
        {
            if (c == ',')
            {
                CityNum[n]=loc->toDouble(st1);
                n++;
                st1.clear();
            }
            else
            {
                st1=st1+c;
            }
        }
        CityNum[n]=loc->toDouble(st1);

        bool flag=false;
        for (int i=1;i<=n;i++)
        {
            if (CityNum[i]>15||CityNum[i]<1)
            {
                flag=true;
            }
        }

        if(flag==false)
        {
            for (int q=1;q<=n;q++)
            {
                matrix[CityNum[q]][CityNum[q]]=0;
                for(int i=1;i<=15;i++)
                {
                        if (matrix[i][i]==0 && CityNum[q]!=i)
                        {
                            a[i][CityNum[q]]=a[CityNum[q]][i]=matrix[i][CityNum[q]]=matrix[CityNum[q]][i]=rand() % 30+1;
                        }
                }
            }
            for(int i=1;i<=15;i++)
            {
                   if (matrix[i][i]==0) matrix[i][i]=-1;
            }

            ui->textEdit->setText("");
            for (int i=0;i<=15;i++)
            {
                ui->textEdit->insertPlainText(loc->toString(i));
                ui->textEdit->insertPlainText("  ");
            }
            ui->textEdit->append("\n");

            for (int i=1;i<=16;i++)
            {
                for(int j=0;j<=15;j++)
                {
                    ui->textEdit->insertPlainText(loc->toString(matrix[i][j]));
                    ui->textEdit->insertPlainText(" ");
                }
               ui->textEdit->append("\n");
            }
            for(int i=1;i<=15;i++)
            {
                for(int j=i;j<=15;j++)
                {
                    if(matrix[i][j]!=-1)
                    {
                        creatingitem(i,j,matrix[i][j],0);
                    }
                }
            }
            OperatNumber=0;
            ui->tablo_1->setText("");
            ui->tablo_vivod->setText("");
        }
        else
        {
            if(flanguage==true) ui->tablo_vivod->setText("Error: check the city numbers, they should not be <0 and >15!!!");
            else ui->tablo_vivod->setText("Ошибка: проверьте номера городов, они не должны быть <0 и >15!!!");
        }
        ui->tablo_2->setText("");
        ui->tablo_3->setText("");
    }

    if(OperatNumber==2)
    {
        QString st=ui->tablo_1->text();
        int CityNum[4];
        n=1;
        QString st1;
        for (auto c : st)
        {
            if (c == ',')
            {
                CityNum[n]=loc->toDouble(st1);
                n++;
                st1.clear();
            }
            else
            {
                st1=st1+c;
            }
        }
        CityNum[n]=loc->toDouble(st1);

        bool flag=false;
        if (CityNum[1]>15||CityNum[1]<=0||CityNum[2]>15||CityNum[2]<=0) flag=true;

        if (flag==false)
        {
            if (CityNum[3]<=0) CityNum[3]=-1;
             a[CityNum[1]][CityNum[2]]=a[CityNum[2]][CityNum[1]]=matrix[CityNum[1]][CityNum[2]]=matrix[CityNum[2]][CityNum[1]]=CityNum[3];
             scene->clear();
             for(int i=1;i<=15;i++)
             {
                 for(int j=i;j<=15;j++)
                 {
                     if(matrix[i][j]!=-1)
                     {
                         creatingitem(i,j,matrix[i][j],0);
                     }
                 }

                 ui->textEdit->setText("");
                 for (int i=0;i<=15;i++)
                 {
                     ui->textEdit->insertPlainText(loc->toString(i));
                     ui->textEdit->insertPlainText("  ");
                 }
                 ui->textEdit->append("\n");
                 for (int i=1;i<=16;i++)
                 {
                     for(int j=0;j<=15;j++)
                     {
                         ui->textEdit->insertPlainText(loc->toString(matrix[i][j]));
                         ui->textEdit->insertPlainText(" ");
                     }
                    ui->textEdit->append("\n");

                 }
             }
             OperatNumber=0;
             ui->tablo_1->setText("");
             ui->tablo_vivod->setText("");
        }
        else
        {
            if(flanguage==true) ui->tablo_vivod->setText("Error: check the city numbers, they should not be <0 and >15!!!");
            else ui->tablo_vivod->setText("Ошибка: проверьте номера городов, они не должны быть <0 и >15!!!");
        }
        ui->tablo_2->setText("");
        ui->tablo_3->setText("");
    }
    if (OperatNumber==3)
    {
        srand(time(0)) ;
        int ke=0;
        bool flagn=false;
        n=15;
        QString st=ui->tablo_1->text();
        start=loc->toDouble(st);
        bool flagCity=false;
        if (start>15||start<=0) flagCity=true;

        if (flagCity==false)
        {
            for (int i=1;i<=15;i++)
            {
                int k=0;
                for(int j=1;j<=15;j++)
                {
                    if(matrix[i][j]!=-1)
                    {
                        k++;
                    }
                    if(k==2)
                    {
                        ke++;
                        j=15;
                    }
                    if(j==15&&k==1)
                    {
                        flagn=true;
                        i=15;
                    }
                    if(k==0 && i==start && j==15)
                    {
                        flagn=true;
                        i=15;
                    }
                }
            }

            if(flagn==false)
            {
                n2=1;
                for (int i=1;i<=n;i++)
                {
                    for(int j=1;j<=n;j++)
                    {
                        if(matrix[i][j]!=-1)
                        {
                            tabl[n2]=i;
                            n2++;
                            j=n;
                        }
                    }
                }
                n2--;
                for (int i=1;i<=n2;i++)
                {
                    for(int j=i;j<=n2;j++)
                    {
                            a2[i][j]=a2[j][i]=matrix2[i][j]=matrix2[j][i]=-1;

                    }
               }
               for (int i=1;i<=n2;i++)
                {
                   for(int j=i;j<=n2;j++)
                   {
                      a2[i][j]=a2[j][i]=matrix2[i][j]=matrix2[j][i]=a[tabl[i]][tabl[j]];

                    }
               }
               int e = 1;
               while (e != n2 ) //маршрут и путь
               {
                   reduction(); //редукция строк и столбцов
                   function(e);
                   e++;
               }
               int flag = 0,num = 1,f,k = 1;
               while (flag != n2 + 1)
               {
                   f = num;
                   for (int i = 1; i <= n2; i++)
                   {
                       if (way[i][1] == num)
                       {
                           way_1[k] = num;
                           k++;
                           num = way[i][2];
                           flag++;
                           i = n2;
                       }
                   }
                   if (f == num)
                   {
                       int num_2 = 1;
                       int flag2 = false;
                       while (!flag2)
                       {
                           int f2 = num_2;
                           for (int i = 1; i <= n2; i++)
                           {
                               if (way[i][2] == num_2)
                               {
                                   num_2 = way[i][1];
                                   i = n2;
                               }
                           }
                           if (f2 == num_2)
                           {
                               way[n2][1] = num;
                               way[n2][2] = num_2;
                               flag2 = true;
                           }
                       }
                   }
               }

               for (int i = 1; i <= n2 - 1; i++)
               {
                   for (int j = i + 1; j <= n2; j++)
                   {
                       bool flagotr=false;

                       for (int q = 1; q <= n2 - 1; q++)
                       {
                           if (a2[way_1[q]][way_1[q+1]]==-1)
                           {
                               flagotr=true;
                           }
                       }
                       if (way_1[i] == way_1[j] || way_1[1] != way_1[n2 + 1]||flagotr==true)
                       {
                           for (int i = 1; i <= n2; i++)
                           {
                               for (int j = 1; j <= n2; j++)
                               {
                                   if (i == j)
                                   {
                                       matrix2[i][j] = a2[i][j];
                                   }
                                   else
                                   {
                                       matrix2[i][j] = matrix2[j][i] = a2[j][i];
                                   }
                               }
                           }
                           way_1[1] = 1;
                           num = 1;
                           int min;
                           flag = 0;
                           k = 2;
                           while (flag != n2 - 1)
                           {
                               min = 10000;
                               int el = 0;
                               for (int i = 1; i <= n2; i++)
                               {
                                   if (min > matrix2[num][i] && matrix2[num][i] != -1)
                                   {
                                       min = matrix2[num][i];
                                       el = i;
                                   }
                               }
                               for (int i = 1; i <= n2; i++)
                               {
                                   matrix2[num][i] = -1;
                                   matrix2[i][num] = -1;
                               }
                               num = el;
                               way_1[k] = num;
                               k++;
                               flag++;
                           }
                           j = n2;
                           i = n2 - 1;
                       }
                   }
               }
               way_1[n2+1] = 1;
               int last = 1;
               length = 0;
               for (int i = 2; i <= n2 + 1; i++)
               {
                   length = length+a2[last][way_1[i]];
                   last = way_1[i];
               }
               for(int i=1;i<=n2;i++)
               {
                  way_1[i]=tabl[way_1[i]];
               }
               int way_2[16], n_2=0;
               for (int i = 1; i <= n2; i++)
               {
                   if (way_1[i] != start)
                   {
                       way_2[i] = way_1[i];
                   }
                   else n_2 = i;

               }
               for (int i = 1; i <= n2-n_2+1; i++)
               {
                   way_1[i] = way_1[i + n_2 - 1];
               }
               for (int i = n2-n_2+2; i <= n2; i++)
               {
                   way_1[i] = way_2[i - n2 + n_2 - 1];
               }
               way_1[n2+1]=start;
               if(flanguage==true) ui->tablo_2->setText("Route: ");
               else ui->tablo_2->setText("Маршрут: ");
              for (int i = 1; i <= n2; i++)
              {
                   ui->tablo_2->setText(ui->tablo_2->text()+loc->toString(way_1[i]));
                   ui->tablo_2->setText(ui->tablo_2->text()+"->");
                   creatingitem(way_1[i],way_1[i+1],matrix[way_1[i]][way_1[i+1]],1);
              }
               ui->tablo_2->setText(ui->tablo_2->text()+loc->toString(start));
               if(flanguage==true) ui->tablo_3->setText("Route length: "+loc->toString(length));
               else ui->tablo_3->setText("Длина маршрута: "+loc->toString(length));

               OperatNumber=0;
               ui->tablo_1->setText("");
               ui->tablo_vivod->setText("");
           }
           else
           {
               if(flanguage==true) ui->tablo_vivod->setText("Error: each city must have at least 2 routes!!!");
               else ui->tablo_vivod->setText("Ошибка: каждый город должен иметь минимум 2 маршрута!!!");
           }
        }
        else
        {
            if(flanguage==true) ui->tablo_vivod->setText("Error: check the city numbers, they should not be <0 and >15!!!");
            else ui->tablo_vivod->setText("Ошибка: проверьте номера городов, они не должны быть <0 и >15!!!");
        }
    }
}

void cities::on_bclear_clicked()// очистка
{
    scene->clear();
    for(int i=1;i<=15;i++)
    {
        for(int j=1;j<=15;j++)
        {
        a[i] [j] =matrix[i][j]=-1;
        }
        ui->tablo_1->setText("");
        ui->tablo_2->setText("");
        ui->tablo_3->setText("");
        ui->textEdit->setText("");
        ui->tablo_vivod->setText("");
        OperatNumber=0;
    }
}


void cities::on_blanguage_clicked()// язык
{
    if(flanguage==true)
    {
        ui->blanguage->setText("РУС");
        ui->l1->setText("Санкт-Петербург");
        ui->l2->setText("Москва");
        ui->l3->setText("Пермь");
        ui->l4->setText("Тюмень");
        ui->l5->setText("Волгоград");
        ui->l6->setText("Сочи");
        ui->l7->setText("Астрахань");
        ui->l8->setText("Казань");
        ui->l9->setText("Воронеж");
        ui->l10->setText("Архангельск");
        ui->l11->setText("Мурманск");
        ui->l12->setText("Воркута");
        ui->l13->setText("Омск");
        ui->l14->setText("Нов. Уренгой");
        ui->l15->setText("Сургут");
        ui->bvvod->setText("Ввод");
        ui->bSelectCities->setText("Задать города");
        ui->bChangeSize->setText("Изменить размер дороги");
        ui->bCreateARoute->setText("Создать маршрут");
        ui->bclear->setText("Очистить");
        flanguage=false;
    }
    else
    {
        ui->blanguage->setText("ENG");
        ui->l1->setText("Saint-Petersburg");
        ui->l2->setText("Moscow");
        ui->l3->setText("Perm");
        ui->l4->setText("Tyumen");
        ui->l5->setText("Volgograd");
        ui->l6->setText("Sochi");
        ui->l7->setText("Astrakhan");
        ui->l8->setText("Kazan");
        ui->l9->setText("Voronezh");
        ui->l10->setText("Arkhangelsk");
        ui->l11->setText("Murmansk");
        ui->l12->setText("Vorkuta");
        ui->l13->setText("Omsk");
        ui->l14->setText("New Urengoy");
        ui->l15->setText("Surgut");
        ui->bvvod->setText("Enter");
        ui->bSelectCities->setText("Set cities");
        ui->bChangeSize->setText("Change the road size");
        ui->bCreateARoute->setText("Create a route");
        ui->bclear->setText("Clear");
        flanguage=true;
    }
}
