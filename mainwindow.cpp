#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    Cargar();
    desface(time,current);
    Analisis();
    ValorEfectivo();
    PotenciaMecanica();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::showData(){
    qDebug() << "TIME   VOLTAGE CURRENT";
    for(int i=0; i<c; i++){
        qDebug() <<time[i]<<"   "<<voltage[i]<<"   "<<current[i];
    }
}
void MainWindow::plot(QVector<double> &x, QVector<double> &y,QWidget &view, const QColor &color){
    //verifico si esta ventana pertenece a CustomPlot
    QCustomPlot *customPlot = qobject_cast<QCustomPlot*>(&view);
    if(!customPlot){
        qDebug() << "Error: El Widget pasado no es un QCustomPlot";
        return ;
    }
    int n = customPlot->graphCount();
    customPlot->addGraph();
    QPen pen;
    pen.setColor(color);
    customPlot->graph(n)->setPen(pen);
    customPlot->graph(n)->setData(x,y);
    customPlot->rescaleAxes();
    customPlot->replot();
}
void MainWindow::Cargar(){
    FILE *f = fopen("C:\\Users\\macia\\OneDrive\\Documentos\\InformaticaII\\Examen2_macias\\vi_3.dat","rb");
    fseek(f,0,SEEK_END);
    c = ftell(f)/(3*sizeof(double));
    rewind(f);
    if(f){
        voltage.resize(c);
        current.resize(c);
        time.resize(c);

        for(int i=0; i<c; i++){
            fread(&time[i],sizeof(double),1,f);
            fread(&voltage[i],sizeof(double),1,f);
            fread(&current[i],sizeof(double),1,f);
        }
        fclose(f);
        showData();
    }
    plot(time,voltage,*ui->Plot,QColor(Qt::blue));
    plot(time,current,*ui->Plot, QColor(Qt::red));

}
void MainWindow::desface(QVector<double> &v_x, QVector<double> &v_y){
    int a=0,band=0,i=0;
    qDebug()<<c;
    while(band == 0){
        if(v_y[i]<=0){
            a=i;
        }if((v_y[i] >= 0) && (band==0)){
            band=1;
        }
        i++;
    }
    if((v_y[a] != 0) && (a!=0)){
        a = (a -((v_y[a])/(v_y[(a+1)] - v_y[a])));
    }
    double tiempo = v_x[a] - v_x[0];
    fi = (180/(0.01*tiempo));
    qDebug()<<"desface de "<<fi<<"°";
}
void MainWindow::Analisis(){
    double Vmax,Vmin,Imax,Imin;
    for(int i=0; i<(c -1); i++){
        if(i==0){
            Vmax = voltage[i];
            Vmin = voltage[i];
            Imax = current[i];
            Imin = current[i];
        }else{
            if(voltage[i] < Vmin){
                Vmin = voltage[i];
            }
            if(voltage[i] > Vmax){
                Vmax = voltage[i];
            }
            if(current[i] < Imin){
                Imin = current[i];
            }
            if(current[i] > Imax){
                Imax = current[i];
            }
        }
    }

    ui->Vmax->setText(QString("Voltage maximo: %1").arg(Vmax));
    ui->Vmin->setText(QString("Voltage minima: %1").arg(Vmin));
    ui->Imax->setText(QString("Current maxima: %1").arg(Imax));
    ui->Imin->setText(QString("Current minima: %1").arg(Imin));

}
int MainWindow::indice_cercano(const QVector<double> &vector, double y){
    int a;
    for(int i=0; i<vector.size(); i++){
        if(vector[i]<=y){
            a=i;
        }
    }
    return a;
}
void MainWindow::ValorEfectivo(){
    double coef = time[(c-1)] - time[0];
    qDebug() << "coeficiente: "<<coef;
    double Varea=0, Iarea=0;
    for (int i=0; i<(c-1); i++){
        double Vf = (voltage[i+1] * voltage[i+1]);
        double Vi = (voltage[i] * voltage[i]);
        double If = (current[i+1] * current[i+1]);
        double Ii = (current[i] * current[i]);
        Varea += ((time[i+1]-time[i])*((Vf + Vi)/2));
        Iarea += ((time[i+1]-time[i])*((If + Ii)/2));
    }
    qDebug() << "Varea: "<<Varea;
    qDebug() << "Iarea: "<<Iarea;
    Vefect = sqrt(coef*Varea);
    ui->Vefect->setText(QString("Vefec: %1").arg(Vefect));
    Iefect = sqrt(coef*Iarea);
    ui->Iefect->setText(QString("Vefec: %1").arg(Iefect));
}
void MainWindow::PotenciaMecanica(){

}
