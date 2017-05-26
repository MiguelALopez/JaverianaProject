#include "registrar.h"
#include "ui_registrar.h"
#include "validador.h"
#include "QDebug"
#include <QIntValidator>

Registrar::Registrar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registrar)
{
    ui->setupUi(this);

    // Se restringe estos campos a numericos
    ui->lCedula->setValidator(new QIntValidator(this));
    ui->lTelefono->setValidator(new QIntValidator(this));
    ui->lIngresos->setValidator(new QIntValidator(this));

}

Registrar::~Registrar()
{
    delete ui;
}

void Registrar::on_bAceptar_clicked()
{
    QString nombre = ui->lNombre->text();
    QString apellido = ui->lApellido->text();
    QString cedula = ui->lCedula->text();
    QString password = ui->lPasword->text();
    QString fecha = ui->dateNacimiento->date().toString();
    QString telefono = ui->lTelefono->text();
    QString direccion = ui->lDireccion->text();
    QString sexo = ui->comboSexo->currentText();
    QString estado = ui->lEstadoCivil->text();
    QString correo = ui->lCorreo->text();
    QString ingresos = ui->lIngresos->text();


    if(Validador().validarUsuario(cedula, telefono, correo, ingresos, NULL)){
        qDebug() << "raffo ";
    }
}
