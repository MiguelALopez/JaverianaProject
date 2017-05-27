#include "asociadosfondo.h"
#include "ui_asociadosfondo.h"
#include <QIntValidator>
#include <QDebug>
#include <QMessageBox>
#include <QDate>
#include "estadocreditos.h"
#include "estadosauxilio.h"
#include "estadoahorro.h"
#include "pregunta.h"
#include "daousuario.h"
#include "daofondo.h"
#include "daocredito.h"
#include "daoauxilio.h"
#include "daonotificacion.h"
#include "daoahorro.h"
#include "daofaq.h"

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


    double tasa = consulta[1].toFloat();
    double valorAdmin = consulta[5].toDouble();
    double seguro = consulta[6].toDouble();
    double plataforma = consulta[7].toDouble();
    double iva = fondo[2].toDouble();

    float cuota = (float)valorMonto / (float)numCuotas;
    cuota = cuota + (cuota * ((float)tasa / 100.0));

    valorAdmin = valorAdmin + ((float)valorAdmin * ((float) iva / 100.0));
    seguro = seguro + ((float)seguro * ((float) iva / 100.0));
    plataforma = plataforma + ((float)plataforma * ((float) iva / 100.0));

    int total = (cuota * numCuotas) + valorAdmin + seguro + plataforma;

    ui->lSimTasa->setText(QString::number(tasa));
    ui->lSimAdmin->setText(QString::number(valorAdmin));
    ui->lSimSeguro->setText(QString::number(seguro));
    ui->lSimPlataforma->setText(QString::number(plataforma));
    ui->lSimValorCuota->setText(QString::number(cuota, 'g', 15));
    ui->lSimIva->setText(QString::number(iva));

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

    QMessageBox::information(this, "Exito","La solicitud fue enviada con exito");

}

void AsociadosFondo::on_bAuxSolicitud_clicked()
{
    QString tipoAux = ui->cAuxTipo->currentText();
    QString valor = ui->lAuxValor->text();
    QString fechaActual = QDate::currentDate().toString("yyyy-MM-dd");

    DAOAuxilio daoauxilio;
    QString params[6] = {tipoAux, valor, "0", fechaActual, "Pendiente", cedula};
    daoauxilio.CrearAuxilio(params);
    QMessageBox::information(this, "Exito","La solicitud fue enviada con exito");
}

void AsociadosFondo::on_bAhoAdiccionar_clicked()
{
    QString valor = ui->lAhoTotal->text();
    QString fecha = QDate::currentDate().toString("yyyy-M-d");

    QString data[3];
    data[0] = valor;
    data[1] = fecha;
    data[2] = cedula;

    DAOAhorro daoAhorro;
    daoAhorro.CrearAhorro(data);
    QMessageBox::information(this, "Exito","El ahorro se almaceno con exito");
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
    QString fecha = ui->dateUserNacimiento->text();
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
    }else if(index == 3){
        DAOFondo daoFondo;
        QList<QString> ahorro = daoFondo.ConsultarPropiedadesAhorro();

        DAOUsuario daoUsuario;
        QList<QString> usuario = daoUsuario.ConsultarUsuario(cedula);

        ui->lAhoSalario->setText(usuario[10]);
        ui->sAhoTasa->setMinimum(ahorro[2].toInt());
        ui->sAhoTasa->setMaximum(ahorro[1].toInt());
        double tasa = (double)ui->sAhoTasa->value() / 100;
        double salario = usuario[10].toInt();
        double aho = (salario * tasa);
        salario -= aho;
        ui->lAhoSalarioFinal->setText(QString::number(salario, 'g', 15));
        ui->lAhoTotal->setText(QString::number(aho, 'g', 15));

    }else if(index == 4){
        DAOFaq daoFaq;
        QList<QList<QString>> consulta = daoFaq.ConsultarFaq("Resuelto");

        ui->tFaq->setRowCount(consulta.length());
        for(int i=0; i<consulta.length(); i++){
            for(int j=0; j<3; j++){
                QString dato="";
                if (j==0)
                    dato = consulta[i][1];
                if (j==1)
                    dato = consulta[i][2];
                if (j==2)
                    dato = consulta[i][5];
                ui->tFaq->setItem(i, j, new QTableWidgetItem(dato));
            }
        }
    }else if(index == 5){
        DAONotificacion daoNotificacion;
        QList<QList<QString>> consulta = daoNotificacion.ConsultarNotificacion(cedula);

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
}

void AsociadosFondo::on_sAhoTasa_valueChanged(int arg1)
{
    double salario = ui->lAhoSalario->text().toDouble();
    double tasa = (double)arg1 / 100.0;
    double ahorro = salario * tasa;
    double salarioFinal = salario - ahorro;

    ui->lAhoSalarioFinal->setText(QString::number(salarioFinal, 'g', 15));
    ui->lAhoTotal->setText(QString::number(ahorro, 'g', 15));
}

void AsociadosFondo::on_bFaqPregunta_clicked()
{
    Pregunta *p = new Pregunta(cedula);
    p->show();
}
