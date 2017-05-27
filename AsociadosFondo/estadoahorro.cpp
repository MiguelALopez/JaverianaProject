#include "estadoahorro.h"
#include "ui_estadoahorro.h"
#include "daoahorro.h"
#include <QString>
#include <QDebug>
#include <QList>

EstadoAhorro::EstadoAhorro(QString cedula, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EstadoAhorro)
{
    ui->setupUi(this);
    this->cedula = cedula;
    double total = 0;
    DAOAhorro daoahorro;
    QList<QList<QString>> consulta = daoahorro.ConsultarAhorro(cedula);
    ui->tAhorros->setRowCount(consulta.length());
    for(int i=0; i<consulta.length(); i++){
        for(int j=0; j<2; j++){
            QString dato="";
            if (j==0)
                dato = consulta[i][2];
            if (j==1){
                dato = consulta[i][1];
                total += dato.toDouble();
            }
            ui->tAhorros->setItem(i, j, new QTableWidgetItem(dato));
        }
    }
    ui->lTotalAhorro->setText(QString::number(total));
    ui->lTotalAhorro->setEnabled(true);
}

EstadoAhorro::~EstadoAhorro()
{
    delete ui;
}

void EstadoAhorro::on_bActualizar_clicked(){
    double total = 0;
    DAOAhorro daoahorro;
    QList<QList<QString>> consulta = daoahorro.ConsultarAhorro(cedula);
    ui->tAhorros->setRowCount(consulta.length());
    for(int i=0; i<consulta.length(); i++){
        for(int j=0; j<2; j++){
            QString dato="";
            if (j==0)
                dato = consulta[i][2];
            if (j==1){
                dato = consulta[i][1];
                total += dato.toDouble();
            }
            ui->tAhorros->setItem(i, j, new QTableWidgetItem(dato));
        }
    }
    ui->lTotalAhorro->setText(QString::number(total));
    ui->lTotalAhorro->setEnabled(true);
}
