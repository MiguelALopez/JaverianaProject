#include "estadocreditos.h"
#include "ui_estadocreditos.h"
#include "daocredito.h"
#include <QString>
#include <QDebug>
#include <QList>

EstadoCreditos::EstadoCreditos(QString cedula, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EstadoCreditos)
{
    ui->setupUi(this);
    this->cedula = cedula;
    DAOCredito daocredito;
    QList<QList<QString>> consulta = daocredito.ConsultarCredito(cedula);
    ui->tCreditos->setRowCount(consulta.length());
    for(int i=0; i<consulta.length(); i++){
        for(int j=0; j<3; j++){
            QString dato="";
            if (j==0)
                dato = consulta[i][10];
            if (j==1)
                dato = consulta[i][11];
            if (j==2)
                dato = consulta[i][9];
            ui->tCreditos->setItem(i, j, new QTableWidgetItem(dato));
        }
    }
}

EstadoCreditos::~EstadoCreditos()
{
    delete ui;
}

void EstadoCreditos::on_bActualizar_clicked(){
    DAOCredito daocredito;
    QList<QList<QString>> consulta = daocredito.ConsultarCredito(cedula);
    ui->tCreditos->setRowCount(consulta.length());
    for(int i=0; i<consulta.length(); i++){
        for(int j=0; j<3; j++){
            QString dato="";
            if (j==0)
                dato = consulta[i][10];
            if (j==1)
                dato = consulta[i][11];
            if (j==2)
                dato = consulta[i][9];
            ui->tCreditos->setItem(i, j, new QTableWidgetItem(dato));
        }
    }
}

void EstadoCreditos::on_bCerrar_clicked()
{
    close();
}
