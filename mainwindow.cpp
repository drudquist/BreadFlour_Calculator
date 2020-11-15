#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QRegExpValidator>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //allow only numbers and decimal point
    ui->bf_Amount->setValidator(new QRegExpValidator(QRegExp("^\\d*(\\.\\d+)?$")));
    ui->apf_Amount->setValidator(new QRegExpValidator(QRegExp("^\\d*(\\.\\d+)?$")));
    ui->vwg_Amount->setValidator(new QRegExpValidator(QRegExp("^\\d*(\\.\\d+)?$")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

