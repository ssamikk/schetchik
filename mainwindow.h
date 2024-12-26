#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "schetchik.h"
#include "tablemodel.h"

#include <QMainWindow>
#include <thread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool load();
    QVector<int> &getV();
public slots:
    void intervalChanged(const QString&str);
    void blockModel();
    void unblockModel();
private slots:
    void addToTable();
    void remFromTable();
    void save();
private:
    QVector<int> v;
    TableModel model;
    Schetchik schetch;
    std::thread thr;
    Ui::MainWindow *ui;
};

namespace Index {
    bool Comporater(QModelIndex const &in1, QModelIndex const &in2);
}

#endif // MAINWINDOW_H
