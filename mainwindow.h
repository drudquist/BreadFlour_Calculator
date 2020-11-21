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

    enum class Units{
        eCUPS,
        eTBSP,
        eTSP,
        eGRAMS,
        eOUNCES,
    };

    enum class Ingredient{
        eBREAD_FLOUR,
        eALL_PURPOSE_FLOUR,
        eVITAL_WHEAT_GLUTEN,
    };

private:
    Ui::MainWindow *ui;

    double ConvertUnits(Units convertFrom, Units convertTo, double value, Ingredient ingredient) const;
    double CalculateVitalWheatGlutenPercentage(double tpp, double fpp, double vwgpp) const;
    double CalculateAllPurposeFlourPercentage(double vwg_Percentage, double tpp, double fpp, double vwgpp) const;


private slots:
    void Calculate();

};
#endif // MAINWINDOW_H
