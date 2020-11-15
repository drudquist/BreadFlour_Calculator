#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QRegExpValidator>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //allow only numbers
    ui->bf_Amount->setValidator(new QRegExpValidator(QRegExp("[0-9]+,[0-9][0-9]*")));
    ui->apf_Amount->setValidator(new QRegExpValidator(QRegExp("[0-9]+,[0-9][0-9]*")));
    ui->vwg_Amount->setValidator(new QRegExpValidator(QRegExp("[0-9]+,[0-9][0-9]*")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

