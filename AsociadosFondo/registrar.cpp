#include "registrar.h"
#include "ui_registrar.h"
#include "validador.h"
#include "QDebug"
#include <QIntValidator>
#include <QMessageBox>
#include "daousuario.h"

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
    QString params[11];


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

    params[0] = cedula;
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


    if(Validador().validarUsuario(cedula, telefono, correo, ingresos, NULL)){
        DAOUsuario daoUsuario;
        daoUsuario.CrearUsuario(params);
        QMessageBox::information(this, "Exito","El usuario fue creado con exito");
        close();
    }
}
