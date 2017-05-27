#include "asociadosfondo.h"
#include "ui_asociadosfondo.h"
#include <QIntValidator>
#include <QDebug>
#include <QMessageBox>
#include <QDate>
#include "estadocreditos.h"
#include "estadosauxilio.h"
#include "estadoahorro.h"
#include "daousuario.h"
#include "daofondo.h"
#include "daocredito.h"
#include "daoauxilio.h"
#include "daonotificacion.h"

AsociadosFondo::AsociadosFondo(QString cedula, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AsociadosFondo)
{
    ui->setupUi(this);
    this->cedula = cedula;

    // Se restringen estos campos a numerico
    ui->lSimMonto->setValidator(new QIntValidator(0, 50000000, this));
    ui->lSimNumCuota->setValidator(new QIntValidator(this));

    ui->lCredFamilia->setValidator(new QIntValidator(this));
    ui->lCredTel->setValidator(new QIntValidator(this));
    ui->lCredTiempo->setValidator(new QIntValidator(this));
    ui->lCredGastos->setValidator(new QIntValidator(this));
    ui->lCredPrestamo->setValidator(new QIntValidator(this));
    ui->lCredPlazo->setValidator(new QIntValidator(this));
    ui->lCredMeses->setValidator(new QIntValidator(this));

    ui->lAuxValor->setValidator(new QIntValidator(this));

    ui->lUserCedula->setValidator(new QIntValidator(this));
    ui->lUserTelefono->setValidator(new QIntValidator(this));
    ui->lUserIngresos->setValidator(new QIntValidator(this));
}

AsociadosFondo::~AsociadosFondo()
{
    delete ui;
}

void AsociadosFondo::on_bSalir_clicked()
{
    close();
}

void AsociadosFondo::on_bSimular_clicked()
{
    DAOFondo daoFondo;
    QList<QString> consulta = daoFondo.ConsultarPropiedadesCredito();
    QList<QString> fondo = daoFondo.ConsultarFondo();

    int valorMonto = ui->lSimMonto->text().toInt();
    int numCuotas = ui->lSimNumCuota->text().toInt();


    int tasa = consulta[1].toInt();
    int valorAdmin = consulta[5].toInt();
    int seguro = consulta[6].toInt();
    int plataforma = consulta[7].toInt();
    int iva = fondo[2].toInt();

    ui->lSimTasa->setText(QString::number(tasa));
    ui->lSimAdmin->setText(QString::number(valorAdmin));
    ui->lSimSeguro->setText(QString::number(seguro));
    ui->lSimPlataforma->setText(QString::number(plataforma));
    ui->lSimIva->setText(QString::number(iva));

    double cuota = (double)valorMonto / (double)numCuotas;
    cuota = cuota + (cuota * ((double)tasa / 100.0));

    valorAdmin = valorAdmin + ((double)valorAdmin * ((double) iva / 100.0));
    seguro = seguro + ((double)seguro * ((double) iva / 100.0));
    plataforma = plataforma + ((double)plataforma * ((double) iva / 100.0));

    int total = (cuota * numCuotas) + valorAdmin + seguro + plataforma;

    ui->lSimTotal->setText(QString::number(total));

}

void AsociadosFondo::on_bCredSolicitud_clicked()
{
    QString ingresoFamiliar = ui->lCredFamilia->text();
    QString nombreEmpresa = ui->lCredEmpresa->text();
    QString telefonoEmpresa = ui->lCredTel->text();
    QString tiempoLaborando = ui->lCredTiempo->text();
    QString totalGastos = ui->lCredGastos->text();
    QString valorPrestamo = ui->lCredPrestamo->text();
    QString plazoCredito = ui->lCredPlazo->text();
    QString fondoMeses = ui->lCredMeses->text();
    QString fechaActual = QDate::currentDate().toString("yyyy-MM-dd");
    qDebug() << fechaActual;

    DAOCredito daocredito;
    QString params[12] = {ingresoFamiliar, nombreEmpresa, telefonoEmpresa, tiempoLaborando, valorPrestamo, totalGastos, plazoCredito,
                      fondoMeses, "0", fechaActual, "Pendiente", cedula};
    daocredito.CrearCredito(params);

}

void AsociadosFondo::on_bAuxSolicitud_clicked()
{
    QString tipoAux = ui->cAuxTipo->currentText();
    QString valor = ui->lAuxValor->text();
    QString fechaActual = QDate::currentDate().toString("yyyy-MM-dd");

    DAOAuxilio daoauxilio;
    QString params[6] = {tipoAux, valor, "0", fechaActual, "Pendiente", cedula};
    daoauxilio.CrearAuxilio(params);
}

void AsociadosFondo::on_bAhoAdiccionar_clicked()
{
    QString ahorro = ui->lAhoTotal->text();
    QString fecha = QDate::currentDate().toString("yyyy-M-d");

    qDebug() << fecha;
}

void AsociadosFondo::on_bCredConsulta_clicked()
{
    EstadoCreditos *c = new EstadoCreditos(cedula);
    c->show();
}

void AsociadosFondo::on_bAuxConsulta_clicked()
{
    EstadosAuxilio *a = new EstadosAuxilio(cedula);
    a->show();
}

void AsociadosFondo::on_bAhoConsulta_clicked()
{
    EstadoAhorro *a = new EstadoAhorro(cedula);
    a->show();
}

void AsociadosFondo::on_bNotificActualizar_clicked(){
    DAONotificacion daonotificacion;
    QList<QList<QString>> consulta = daonotificacion.ConsultarNotificacion(cedula);
    ui->tNotific->setRowCount(consulta.length());
    for(int i=0; i<consulta.length(); i++){
        for(int j=0; j<3; j++){
            QString dato="";
            if (j==0)
                dato = consulta[i][1];
            if (j==1)
                dato = consulta[i][3];
            if (j==2)
                dato = consulta[i][2];
            ui->tNotific->setItem(i, j, new QTableWidgetItem(dato));
        }
    }
}

void AsociadosFondo::on_bUserGuardar_clicked()
{
    QString params[11];

    QString nombre = ui->lUserNombre->text();
    QString apellido = ui->lUserApellido->text();
    QString ced = ui->lUserCedula->text();
    QString password = ui->lUserPassword->text();
    QString fecha = ui->dateUserNacimiento->text().toString("yyyy-MM-dd");
    QString telefono = ui->lUserTelefono->text();
    QString direccion = ui->lUserDireccion->text();
    QString sexo = ui->comboUserSexo->currentText();
    QString estado = ui->lUserEstadoCivil->text();
    QString correo = ui->lUserCorreo->text();
    QString ingresos = ui->lUserIngresos->text();

    params[0] = ced;
    params[1] = password;
    params[2] = nombre;
    params[3] = apellido;
    params[4] = fecha;
    params[5] = telefono;
    params[6] = direccion;
    params[7] = sexo;
    params[8] = estado;
    params[9] = correo;
    params[10] = ingresos;

    DAOUsuario daoUsuario;
    daoUsuario.ActualizarUsuario(params);

    QMessageBox::information(this, "Exito","El usuario fue modificado correctamente");
}

void AsociadosFondo::on_tabWidget_currentChanged(int index)
{
    if(index == 6){
        DAOUsuario daoUsuario;
        QList<QString> usuario = daoUsuario.ConsultarUsuario(cedula);

        ui->lUserCedula->setText(usuario[0]);
        ui->lUserPassword->setText(usuario[1]);
        ui->lUserNombre->setText(usuario[2]);
        ui->lUserApellido->setText(usuario[3]);
        ui->dateUserNacimiento->setDate(QDate().fromString(usuario[4], "YYYY-M-d"));
        ui->lUserTelefono->setText(usuario[5]);
        ui->lUserDireccion->setText(usuario[6]);
        ui->comboUserSexo->setCurrentText(usuario[7]);
        ui->lUserEstadoCivil->setText(usuario[8]);
        ui->lUserCorreo->setText(usuario[9]);
        ui->lUserIngresos->setText(usuario[10]);
    }
}
