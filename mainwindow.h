#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAbstractButton;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    Ui::MainWindow *ui;

    double CalculateVitalWheatGlutenPercentage(double tpp, double fpp, double vwgpp) const;
    double CalculateAllPurposeFlourPercentage(double vwg_Percentage, double tpp, double fpp, double vwgpp) const;


private slots:
    void Calculate();

};
#endif // MAINWINDOW_H
