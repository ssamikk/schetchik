#include "mainwindow.h"
#include "schetchik.h"
#include <thread>
#include <QDebug>
#include <iostream>
#include <QVector>
#include <QApplication>
#include <QGenericArgument>

Schetchik::Schetchik(QVector<int> *v, QObject *parent): QObject(parent), timer(1)
{
    this->v = v;
}

void Schetchik::runSchetchik(MainWindow *window)
{
    QString data = QString::number(timer);
    QMetaObject::invokeMethod(window, "intervalChanged", QGenericArgument("QString", &data));
    window->intervalChanged(QString::number(timer));
    while(true){
        int summT0 = 0, summT1 = 0;
        QMetaObject::invokeMethod(window, "blockModel");
        for (int i = 0, count = v->size(); i < count; ++i) {
            int value = v->at(i);
            summT0+=value;
            v->replace(i, ++value);
            summT1+=value;
        }
        QMetaObject::invokeMethod(window, "unblockModel");
        qDebug()<<"time"<<summT1<<summT0<<timer<<(summT1-summT0)/timer;
        timer = qMax(1, (summT1-summT0)/timer);
        data = QString::number(timer);
        QMetaObject::invokeMethod(window, "intervalChanged", QGenericArgument("QString", &data));
        std::this_thread::sleep_for(std::chrono::seconds(timer));
    }
}
