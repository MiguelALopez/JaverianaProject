#include "login.h"
#include "ui_login.h"
#include "registrar.h"
#include "asociadosfondo.h"
#include "QDebug"
#include <QMessageBox>

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
    QString cedula = ui->lCedula->text();
    QString password = ui->lPassword->text();

    if(true){
        AsociadosFondo *a = new AsociadosFondo(cedula);
        a->show();
        this->close();
    }else{
        QMessageBox::information(this, "Error","El suuario o contraseña son incorrectos");
    }


}

void Login::on_bRegistrarse_clicked()
{
    Registrar *r = new Registrar();
    r->show();
}
