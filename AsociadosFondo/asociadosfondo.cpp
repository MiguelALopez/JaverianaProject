#include "asociadosfondo.h"
#include "ui_asociadosfondo.h"
#include <QIntValidator>
#include <QDebug>
#include "estadocreditos.h"
#include "estadosauxilio.h"
#include "estadoahorro.h"

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
    int valorMonto = ui->lSimMonto->text().toInt();
    int numCuotas = ui->lSimNumCuota->text().toInt();

    int tasa = ui->lSimTasa->text().toInt();
    int valorAdmin = ui->lSimAdmin->text().toInt();
    int seguro = ui->lSimSeguro->text().toInt();
    int plataforma = ui->lSimPlataforma->text().toInt();
    int iva = ui->lSimIva->text().toInt();

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
}

void AsociadosFondo::on_bAuxSolicitud_clicked()
{
    QString tipoAux = ui->cAuxTipo->currentText();
    QString valor = ui->lAuxValor->text();
}

void AsociadosFondo::on_bAhoAdiccionar_clicked()
{
    QString ahorro = ui->lAhoTotal->text();
    QString fecha = QDate::currentDate().toString("yyyy-M-d");

    qDebug() << fecha;
}

void AsociadosFondo::on_bCredConsulta_clicked()
{
    EstadoCreditos *c = new EstadoCreditos();
    c->show();
}

void AsociadosFondo::on_bAuxConsulta_clicked()
{
    EstadosAuxilio *a = new EstadosAuxilio();
    a->show();
}

void AsociadosFondo::on_bAhoConsulta_clicked()
{
    EstadoAhorro *a = new EstadoAhorro();
    a->show();
}

void AsociadosFondo::on_bUserGuardar_clicked()
{
    QString nombre = ui->lUserNombre->text();
    QString apellido = ui->lUserApellido->text();
    QString ced = ui->lUserCedula->text();
    QString password = ui->lUserPassword->text();
    QString fecha = ui->dateUserNacimiento->text();
    QString telefono = ui->lUserTelefono->text();
    QString direccion = ui->lUserDireccion->text();
    QString sexo = ui->comboUserSexo->currentText();
    QString estado = ui->lUserEstadoCivil->text();
    QString correo = ui->lUserCorreo->text();
    QString ingresos = ui->lUserIngresos->text();
}
