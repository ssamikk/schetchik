#include "mainwindow.h"
#include "schetchik.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), model(&v), schetch(&v), thr(&Schetchik::runSchetchik, &schetch, this),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(&model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(ui->actionAdd, &QAction::triggered, this, &MainWindow::addToTable);
    connect(ui->actionRem, &QAction::triggered, this, &MainWindow::remFromTable);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::save);
    thr.detach();
    connect(&schetch, &Schetchik::intervalChanged, ui->label, &QLabel::setText);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::load()
{
    QSqlQuery query;
    QString str = "CREATE TABLE schetchiks (number INTEGER);";
    if (!query.exec(str)) {
        qDebug() << "Table alrady enable"<<query.lastError();
    }
    str = "SELECT number FROM schetchiks";
    if (!query.exec(str)) {
        qCritical() << "SQL error"<<query.lastError();
        return false;
    }
    model.beginReset();
    while (query.next()) {
        v.append(query.value(0).toInt());
    }
    model.endReset();
    return true;
}

void MainWindow::addToTable()
{
    model.insertRow(model.rowCount());
}

void MainWindow::remFromTable()
{
    QModelIndexList rowSel = ui->tableView->selectionModel()->selectedRows();
    std::sort(rowSel.begin(), rowSel.end(), &Index::Comporater);
    for(QModelIndex index : rowSel){
        model.removeRow(index.row());
    }
}

void MainWindow::save()
{
    QSqlQuery query;
    QString str = "DELETE FROM schetchiks";
    if (!query.exec(str)) {
        qCritical() << "Unabe to make DELETE operation"<<query.lastError();
        return;
    }
    str = "INSERT INTO schetchiks (number) VALUES(%1);";
    for(const int &i : v){
        if (!query.exec(str.arg(i))) {
            qCritical() << "Unabe to make insert operation"<<query.lastError();
            return;
        }
    }
    QMessageBox::information(this, QString::fromUtf8("Сохранение данных"),
                             QString::fromUtf8("Данные успешно сохранены!"), QMessageBox::Ok);
}

QVector<int> &MainWindow::getV()
{
    return v;
}

void MainWindow::intervalChanged(const QString &str)
{
    ui->label->setText(u8"Интервал: " + str);
}

void MainWindow::blockModel()
{
    model.beginReset();
}

void MainWindow::unblockModel()
{
    model.endReset();
}

bool Index::Comporater(const QModelIndex &in1, const QModelIndex &in2)
{
    if ( !in1.isValid() ) {
        return false;
    }
    if ( !in2.isValid() ) {
        return true;
    }
    return in1.row() > in2.row();
}
