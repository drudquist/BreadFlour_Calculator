#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QRegExpValidator>

/*Terminology
    TPP = target protein percentage
    FPP = flour protein percentage
    VWGPP = vital wheat gluten protein percentage
    apf_Percentage = percent of all purpose flour to use
    vwg_Percentage = percent of vital wheat gluten to use

    apf_Percentage = ( TPP - VWGPP * vwg_Percentage) / FPP
    vwg_Percentage = ( 100 * FPP -  100 * TPP ) / ( FPP - VWGPP * ( 100 - FPP ) )
*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    const auto number_decimal_only = QRegExp("^\\d*(\\.\\d+)?$");
    //allow only numbers and decimal point
    ui->bf_Amount->setValidator(new QRegExpValidator(number_decimal_only));
    ui->apf_Amount->setValidator(new QRegExpValidator(number_decimal_only));
    ui->vwg_Amount->setValidator(new QRegExpValidator(number_decimal_only));
    ui->bf_ProteinPct->setValidator(new QRegExpValidator(number_decimal_only));
    ui->apf_ProteinPct->setValidator(new QRegExpValidator(number_decimal_only));
    ui->vwg_ProteinPct->setValidator(new QRegExpValidator(number_decimal_only));

    connect(ui->calculate, SIGNAL(clicked()), this, SLOT(Calculate()));
    connect(ui->clear, SIGNAL(clicked()), this, SLOT(Clear()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Calculate()
{
     const QPushButton* const button = static_cast<const QPushButton*>(sender());

     if(button != ui->calculate)
     {
         //application is broken
         throw;
     }

    //Get User Input
    const double bf_Amount = ui->bf_Amount->text().toDouble();
    const double tpp = ui->bf_ProteinPct->text().toDouble();
    const double fpp = ui->apf_ProteinPct->text().toDouble();
    const double vwgpp = ui->vwg_ProteinPct->text().toDouble();


    if(bf_Amount <= 0.0 || tpp <= 0.0 || fpp <= 0.0 || vwgpp <= 0.0)
    {
       QMessageBox::warning(this, "Warning", "Values must be greater than zero.");
        return;
    }

    //apf_ProteinPct cannot be greater than vwg_ProteinPct
    if(fpp >= vwgpp)
    {
        QMessageBox::warning(this, "Warning", "All purpose flour protein percentage cannot be greater than vital wheat gluten percentage.");
        return;
    }

    //Calculate Percentages
    const double vwg_Percentage = CalculateVitalWheatGlutenPercentage(tpp, fpp, vwgpp);
    const double apf_Percentage = CalculateAllPurposeFlourPercentage(vwg_Percentage, tpp, fpp, vwgpp);

    //Calculate Amounts
    const double vwg_Amount = bf_Amount * vwg_Percentage;
    const double apf_Amount = bf_Amount * apf_Percentage;

    //TODO: needs truncation
    ui->vwg_Amount->setText(QString::number(vwg_Amount));
    ui->apf_Amount->setText(QString::number(apf_Amount));
}

void MainWindow::Clear()
{
    const QPushButton* const button = static_cast<const QPushButton*>(sender());

    if(button != ui->clear)
    {
        //application is broken
        throw;
    }

    ui->bf_Amount->setText("");
    ui->apf_Amount->setText("");
    ui->vwg_Amount->setText("");

    ui->bf_ProteinPct->setText("");
    ui->apf_ProteinPct->setText("");
    ui->vwg_ProteinPct->setText("");
}

double MainWindow::CalculateVitalWheatGlutenPercentage(const double tpp, const double fpp, const double vwgpp) const
{
    //vwg_Percentage = ( 100 * FPP -  100 * TPP ) / ( FPP - VWGPP * ( 100 - FPP ) )

    return ( 100 * fpp - 100 * tpp ) / ( fpp - vwgpp * ( 100 - fpp ) );
}

double MainWindow::CalculateAllPurposeFlourPercentage(const double vwg_Percentage, const double tpp, const double fpp, const double vwgpp) const
{
    //apf_Percentage = ( TPP - VWGPP * vwg_Percentage) / FPP

    return ( tpp - vwgpp * vwg_Percentage ) / fpp;
}
