#include "console.h"
#include "mainwindow.h"
#include <QDebug>
#include <QScrollBar>
#include <QBitArray>
#include <bitset>
#include <iostream>
#include <QCharRef>

CONSOLE::CONSOLE(QWidget *parent) :
QPlainTextEdit(parent){
    count = 0;
    N = 0;
    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::white);
    p.setColor(QPalette::Text, Qt::black);
    setPalette(p);
}


void CONSOLE::putData(const int data, QCustomPlot &Graph){

    float output_float;
    qDebug() << data;
    output_float = (float) data / 1000;
    Y.insert(N,output_float);
    QScrollBar *bar = verticalScrollBar();
    bar->setValue(bar->maximum());
    clear();
    insertPlainText(QString::number(data));
    insertPlainText("    ");
    insertPlainText(QString::number(output_float));


        QVector<double> x(N); //Массивы координат точек

        //Вычисляем наши данные
        int i=0;
        for (double X=0; X<N; X++)//Пробегаем по всем точкам
        {
             x[i] = X;
             i++;
        }

        Graph.clearGraphs();//Если нужно, но очищаем все графики
            //Добавляем один график в widget
        Graph.addGraph();
          //Говорим, что отрисовать нужно график по нашим двум массивам x и y
        Graph.graph(0)->setData(x, Y);

            //Подписываем оси Ox и Oy
        Graph.xAxis->setLabel("x");
        Graph.yAxis->setLabel("y");

            //Установим область, которая будет показываться на графике
        if (N < 200)
            Graph.xAxis->setRange(0, N+2);//Для оси Ox
        else
            Graph.xAxis->setRange(N-200, N+2);//Для оси Ox
        Graph.yAxis->setRange(0, 4.5);//Для оси Oy
        Graph.replot();
        N++;
        firstbyte = "";
        count = 0;
}


void CONSOLE::keyPressEvent(QKeyEvent *e){
    switch (e->key()) {
    case Qt::Key_Backspace:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        break;
    default:
        QPlainTextEdit::keyPressEvent(e);
        emit getData(e->text().toLocal8Bit());
    }
}
