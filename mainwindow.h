#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "qcustomplot.h"
#include <math.h>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
//--------------------------------------------
public:
    void showData();
    int indice_cercano(const QVector<double> &vector, double y);
    double PotenciaMecanica_corr();
private:
    QVector<double> voltage, current, time;
    int c;
    double fi;
    double Vefect, Iefect, Power;
    void Cargar();
    void plot(QVector<double> &x, QVector<double> &y,QWidget &view, const QColor &color);
    void desface(QVector<double> &v_x, QVector<double> &v_y);
    void Analisis();
    void ValorEfectivo();
    void PotenciaMecanica();
};
#endif // MAINWINDOW_H
