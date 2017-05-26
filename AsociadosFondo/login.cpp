#include "login.h"
#include "ui_login.h"
#include "registrar.h"
#include "asociadosfondo.h"
#include "QDebug"
#include <QMessageBox>
#include "daousuario.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_bIngresar_clicked()
{
    DAOUsuario daoUsuario;
    QString cedula = ui->lCedula->text();
    QString password = ui->lPassword->text();

    if(daoUsuario.ConsultarLogin(cedula, password)){
        AsociadosFondo *a = new AsociadosFondo(cedula);
        a->show();
        this->close();
    }else{
        QMessageBox::information(this, "Error","El usuario o contraseña son incorrectos");
    }


}

void Login::on_bRegistrarse_clicked()
{
    Registrar *r = new Registrar();
    r->show();
}
