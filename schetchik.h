#ifndef SCHETCHIK_H
#define SCHETCHIK_H

#include <QObject>
#include <QVector>

class MainWindow;

class Schetchik : public QObject
{
    Q_OBJECT
public:
    Schetchik(QVector<int> *v, QObject *parent = nullptr);
    void runSchetchik(MainWindow *window);
signals:
    void intervalChanged(const QString&);
    void blockModel();
    void unBlockModel();
private:
    int timer;
    QVector<int> *v;
};

#endif // SCHETCHIK_H
