#include "estadosauxilio.h"
#include "ui_estadosauxilio.h"
#include "daoauxilio.h"
#include <QString>
#include <QDebug>
#include <QList>

EstadosAuxilio::EstadosAuxilio(QString cedula, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EstadosAuxilio)
{
    ui->setupUi(this);
    this->cedula = cedula;
    DAOAuxilio daoauxilio;
    QList<QList<QString>> consulta = daoauxilio.ConsultarAuxilio(cedula);
    ui->tAuxilios->setRowCount(consulta.length());
    for(int i=0; i<consulta.length(); i++){
        for(int j=0; j<3; j++){
            QString dato="";
            if (j==0)
                dato = consulta[i][4];
            if (j==1)
                dato = consulta[i][5];
            if (j==2)
                dato = consulta[i][3];
            ui->tAuxilios->setItem(i, j, new QTableWidgetItem(dato));
        }
    }
}

EstadosAuxilio::~EstadosAuxilio()
{
    delete ui;
}

void EstadosAuxilio::on_bActualizar_clicked(){
    DAOAuxilio daoauxilio;
    QList<QList<QString>> consulta = daoauxilio.ConsultarAuxilio(cedula);
    ui->tAuxilios->setRowCount(consulta.length());
    for(int i=0; i<consulta.length(); i++){
        for(int j=0; j<3; j++){
            QString dato="";
            if (j==0)
                dato = consulta[i][4];
            if (j==1)
                dato = consulta[i][5];
            if (j==2)
                dato = consulta[i][3];
            ui->tAuxilios->setItem(i, j, new QTableWidgetItem(dato));
        }
    }
}

void EstadosAuxilio::on_bCerrar_clicked()
{
    close();
}
