#include "fondotrabajadores.h"
#include "daousuario.h"
#include "ui_fondotrabajadores.h"
#include <QIntValidator>
#include <QDebug>
#include <QList>
#include <QDate>
#include <QMessageBox>
#include "daocredito.h"
#include "daoauxilio.h"
#include "daoahorro.h"
#include "daofondo.h"
#include "daonotificacion.h"
#include "daofaq.h"
#include "resolverpregunta.h"

FondoTrabajadores::FondoTrabajadores(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FondoTrabajadores)
{
    ui->setupUi(this);

    ui->lOpcMaxCuotas->setValidator(new QIntValidator(this));
    ui->lOpcAntiguedad->setValidator(new QIntValidator(this));
    ui->lOpcTasaCredito->setValidator(new QIntValidator(this));
    ui->lOpcValorMax->setValidator(new QIntValidator(this));
    ui->lOpcValorAdmin->setValidator(new QIntValidator(this));
    ui->lOpcSeguro->setValidator(new QIntValidator(this));
    ui->lOpcValorPlataforma->setValidator(new QIntValidator(this));
    ui->lOpcSmmlv->setValidator(new QIntValidator(this));
    ui->lOpcIva->setValidator(new QIntValidator(this));

    // Caracteristicas de auxilio
    ui->lOpcTasaCalamidad->setValidator(new QIntValidator(this));
    ui->lOpcTasaEdu->setValidator(new QIntValidator(this));
    ui->lOpcMaxCalamidad->setValidator(new QIntValidator(this));
    ui->lOpcMaxAux->setValidator(new QIntValidator(this));

    // Caracteristicas de ahorro
    ui->lOpcMinTasaAhorro->setValidator(new QIntValidator(this));
    ui->lOpcMaxTasaAhorro->setValidator(new QIntValidator(this));
}

FondoTrabajadores::~FondoTrabajadores()
{
    delete ui;
}

void FondoTrabajadores::on_bCredAceptar_clicked()
{
    QString inicial = ui->dateCredInicial->date().toString("yyyy-MM-dd");
    QString final = ui->dateCredFinal->date().toString("yyyy-MM-dd");
    DAOCredito daocredito;
    QList<QList<QString>> consulta = daocredito.ConsultarCredito(inicial, final, "Pendiente");

    DAOFondo daofondo;
    QList<QString> consultaFondo = daofondo.ConsultarPropiedadesCredito();

    QList<QString> fondo = daofondo.ConsultarFondo();
    int tmax = consultaFondo[3].toInt();
    double antig = consultaFondo[4].toDouble();
    double montomax = consultaFondo[2].toDouble() * fondo[1].toDouble();


    for(int i=0; i<consulta.length(); i++){
        DAOUsuario daousuario;
        double ingresos = daousuario.ConsultarUsuario(consulta[i][13])[10].toDouble();
        double gastos = consulta[i][6].toDouble();
        double ingresosFamiliares = consulta[i][1].toDouble();

        int puntos = 0;

        // Categoria 1
        double disponible = (ingresos - gastos) * 0.25;

        if(disponible > 1.5){
            puntos += 75;
        }else if(disponible > 1){
            puntos += 50;
        }

        // Categoria 2
        int cat2 = qrand() % 40;
        if(cat2 <= 5){
            puntos += 10;
        }else if(cat2 <= 11){
            puntos += 15;
        }else if(cat2 == 12){
            puntos += 25;
        }else if(cat2 <= 23){
            puntos += 30;
        }else if(cat2 >= 24){
            puntos += 55;
        }

        // Categoria 3
        int cat3 = qrand() % 60;
        if(cat3 <= 12){
            puntos += 12;
        }else if(cat3 <=23){
            puntos += 35;
        }else if(cat3 <= 47){
            puntos += 60;
        }else if(cat3 > 48){
            puntos += 75;
        }

        // Categoria 4
        int cat4 = qrand() % 5;
        if(cat4 == 0){
            puntos += 75;
        }else if(cat4 == 1){
            puntos += 60;
        }else if(cat4 == 2){
            puntos +=45;
        }else if(cat4 == 3){
            puntos += 25;
        }else if(cat4 == 4){
            puntos += 20;
        }
        bool valido = true;
        QString motivo = "";
        if(puntos <  200){
            valido = false;
            motivo += "No alcanzo el puntaje";
        }
        if(tmax < consulta[i][7].toInt()){
            valido = false;
            if(motivo != ""){
                motivo += ", Superado el maximo de cuotas";
            }else{
                motivo += "Superado el maximo de cuotas";
            }
        }

        if(antig > consulta[i][8].toDouble()){
            valido = false;
            if(motivo!= ""){
                motivo += ", No cumple con la antiguedad";
            }else{
                motivo += "No cumple con la antiguedad";
            }

        }
        if(montomax < consulta[i][5].toDouble()){
            valido = false;
            if(motivo != ""){
                motivo += ", Supero el monto maximo";
            }else{
                motivo += "Supero el monto maximo";
            }
        }
        if(gastos > ingresosFamiliares){
            valido = false;
            if(motivo != ""){
                motivo += ", Los gastos superan los ingresos familiares";
            }else{
                motivo += "Los gastos superan los ingresos familiares";
            }
        }


        if(valido){
            DAOCredito daocredito1;
            daocredito1.ActualizarEstado(consulta[i][0], "Aprobado", consulta[i][5]);

            DAONotificacion daoNotificacion;
            QString param[4];
            param[0] = "Aprobación credito";
            param[1] = "Su credito fue aprobado";
            param[2] = QDate::currentDate().toString("yyyy-M-d");
            param[3] = consulta[i][13];
            daoNotificacion.CrearNotificacion(param);
        }else{
            DAOCredito daocredito1;
            daocredito1.ActualizarEstado(consulta[i][0], "Rechazado", "0");

            DAONotificacion daoNotificacion;
            QString param[4];
            param[0] = "Aprobación credito";
            param[1] = "Su credito fue rechazado, motivo: " + motivo;
            param[2] = QDate::currentDate().toString("yyyy-M-d");
            param[3] = consulta[i][13];
            daoNotificacion.CrearNotificacion(param);
//            qDebug() << "Se reprueba" << puntos << (tmax>=consulta[i][8].toInt()) << (antig<=consulta[i][4].toDouble()) << (montomax>=consulta[i][5].toDouble());
        }
    }
    QMessageBox::information(this, "Info", "Se acaban de analizar "  + QString::number(consulta.size()) + " creditos");
}

void FondoTrabajadores::on_bAuxAceptar_clicked()
{
    QString inicial = ui->dateAuxInit->date().toString("yyyy-MM-dd");
    QString final = ui->dateAuxFinal->date().toString("yyyy-MM-dd");

    DAOAuxilio daoauxilio;
    QList<QList<QString>> consulta = daoauxilio.ConsultarAuxilio(inicial, final, "Pendiente");

    DAOFondo daofondo;
    QList<QString> consultaFondo = daofondo.ConsultarPropiedadesAuxilio();


    double smmlv = daofondo.ConsultarFondo()[1].toDouble();
    double tasaCala = consultaFondo[1].toDouble() / 100.0;
    double tasaEdu = consultaFondo[2].toDouble() / 100.0;
    double maxCala = consultaFondo[3].toDouble();
    double maxValor = consultaFondo[4].toDouble();

    for(int i=0; i<consulta.length(); i++){
        DAOAuxilio daoauxilio2;
        double cuenta = daoauxilio2.CuentaAuxilios();

        double monto = 0;
        QString ed = "Educativo";
        QString cal = "Calamidad";
        if (consulta[i][1] == ed){
            monto = smmlv * tasaEdu;
        } else if (consulta[i][1] == cal){
            qDebug() << "Calamidad";
            if (consulta[i][2].toDouble() * tasaCala >= smmlv * maxCala)
                monto = smmlv*maxCala;
            else
                monto = consulta[i][2].toDouble() * tasaCala;
        }
        else {
            monto = maxValor + 1;
        }

        qDebug() << "maxValor: " << maxValor << " cuenta+monto: " << cuenta+monto;
        if((maxValor>=cuenta+monto) && (qrand() % 2 == 1))
        {
            qDebug() << (maxValor>=cuenta) << (qrand() % 2 == 1);
            daoauxilio2.ActualizarEstado(consulta[i][0], "Aprobado", QString::number(monto));

            DAONotificacion daoNotificacion;
            QString param[4];
            param[0] = "Aprobación auxilio";
            param[1] = "Su auxilio fue aprobado";
            param[2] = QDate::currentDate().toString("yyyy-M-d");
            param[3] = consulta[i][7];
            daoNotificacion.CrearNotificacion(param);
        }
        else
        {

            daoauxilio2.ActualizarEstado(consulta[i][0], "Rechazado", QString::number(0));

            DAONotificacion daoNotificacion;
            QString param[4];
            param[0] = "Aprobación auxilio";
            param[1] = "Su auxilio fue rechazado";
            param[2] = QDate::currentDate().toString("yyyy-M-d");
            param[3] = consulta[i][7];
            daoNotificacion.CrearNotificacion(param);
        }
    }
    QMessageBox::information(this, "Info", "Se acaban de analizar "  + QString::number(consulta.size()) + " auxilios");
}

void FondoTrabajadores::on_bSalir_clicked()
{
    close();
}

void FondoTrabajadores::on_bCredActualizar_clicked()
{
    QString inicial = ui->dateCredInicial->date().toString("yyyy-MM-dd");
    QString final = ui->dateCredFinal->date().toString("yyyy-MM-dd");

    DAOCredito daocredito;
    QList<QList<QString>> consulta = daocredito.ConsultarCredito(inicial, final, "Aprobado");

    DAOUsuario daousuario;
    double total = 0;

    ui->tCreditos->setRowCount(consulta.length());
    for(int i=0; i<consulta.length(); i++){
        for(int j=0; j<4; j++){
            QString dato="";
            if (j==0)
                dato = consulta[i][10];
            if (j==1)
            {
                dato = daousuario.ConsultarUsuario(consulta[i][13])[2];
            }
            if (j==2)
                dato = daousuario.ConsultarUsuario(consulta[i][13])[3];
            if (j==3)
            {
                dato = consulta[i][5];
                total += dato.toDouble();
            }

            ui->tCreditos->setItem(i, j, new QTableWidgetItem(dato));
        }
    }
    ui->lCredNumTotal->setText(QString::number(consulta.length()));
    ui->lCredNumTotal->setEnabled(true);

    ui->lCredValorTotal->setText(QString::number(total, 'g', 15));
    ui->lCredValorTotal->setEnabled(true);
}

void FondoTrabajadores::on_bAuxActualizar_clicked()
{
    QString inicial = ui->dateAuxInit->date().toString("yyyy-MM-dd");
    QString final = ui->dateAuxFinal->date().toString("yyyy-MM-dd");

    DAOAuxilio daoauxilio;
    QList<QList<QString>> consulta = daoauxilio.ConsultarAuxilio(inicial, final, "Aprobado");

    DAOUsuario daousuario;
    double total = 0;

    ui->tAuxilio->setRowCount(consulta.length());
    for(int i=0; i<consulta.length(); i++){
        for(int j=0; j<5; j++){
            QString dato="";
            if (j==0)
                dato = consulta[i][4];
            if (j==1)
            {
                dato = daousuario.ConsultarUsuario(consulta[i][7])[2];
            }
            if (j==2)
                dato = daousuario.ConsultarUsuario(consulta[i][7])[3];
            if (j==3)
            {
                dato = consulta[i][1];
            }
            if (j==4)
            {
                dato = consulta[i][3];
                total += dato.toDouble();
            }

            ui->tAuxilio->setItem(i, j, new QTableWidgetItem(dato));
        }
    }
    ui->lAuxValorTotal->setText(QString::number(total));
    ui->lAuxValorTotal->setEnabled(true);
    ui->lAuxNumTotal->setText(QString::number(consulta.length()));
    ui->lAuxNumTotal->setEnabled(true);
}

void FondoTrabajadores::on_bAhoActualizar_clicked()
{
    QString inicial = ui->dateAhoInit->date().toString("yyyy-MM-dd");
    QString final = ui->dateAhoFinal->date().toString("yyyy-MM-dd");

    DAOAhorro daoahorro;
    QList<QList<QString>> consulta = daoahorro.ConsultarAhorro(inicial, final);

    DAOUsuario daousuario;
    double total = 0;

    ui->tAhorro->setRowCount(consulta.length());
    for(int i=0; i<consulta.length(); i++){
        for(int j=0; j<4; j++){
            QString dato="";
            if (j==0)
                dato = consulta[i][2];
            if (j==1)
            {
                dato = daousuario.ConsultarUsuario(consulta[i][4])[2];
            }
            if (j==2)
                dato = daousuario.ConsultarUsuario(consulta[i][4])[3];
            if (j==3)
            {
                dato = consulta[i][1];
                total += dato.toDouble();
            }

            ui->tAhorro->setItem(i, j, new QTableWidgetItem(dato));
        }
    }
    ui->lAhoValorTotal->setText(QString::number(total, 'g', 15));
    ui->lAhoNumTotal->setText(QString::number(consulta.length()));
}

void FondoTrabajadores::on_bOpcGuardar_clicked()
{
    // Caracteristicas de creditos
    QString maxCuotas = ui->lOpcMaxCuotas->text();
    QString antiguedad = ui->lOpcAntiguedad->text();
    QString tasaCredito = ui->lOpcTasaCredito->text();
    QString valorMax = ui->lOpcValorMax->text();
    QString valorAdmin = ui->lOpcValorAdmin->text();
    QString valorSeguro = ui->lOpcSeguro->text();
    QString valorPlataforma = ui->lOpcValorPlataforma->text();
    QString smmlv = ui->lOpcSmmlv->text();
    QString iva = ui->lOpcIva->text();

    // Caracteristicas de auxilio
    QString tasaCalamidad = ui->lOpcTasaCalamidad->text();
    QString tasaEducacion = ui->lOpcTasaEdu->text();
    QString maxCalamidad = ui->lOpcMaxCalamidad->text();
    QString maxAux = ui->lOpcMaxAux->text();

    // Caracteristicas de ahorro
    QString minTasaAhorro = ui->lOpcMinTasaAhorro->text();
    QString maxTasaAhorro = ui->lOpcMaxTasaAhorro->text();

    DAOFondo daofondo;

    QString paramsFondo[2] = {smmlv, iva};
    daofondo.ActualizarFondo(paramsFondo);

    QString paramsCredito[7] = {tasaCredito, valorMax, maxCuotas, antiguedad, valorAdmin, valorSeguro, valorPlataforma};
    daofondo.ActualizarPropiedadesCredito(paramsCredito);

    QString paramsAuxilio[4] = {tasaCalamidad, tasaEducacion, maxCalamidad, maxAux};
    daofondo.ActualizarPropiedadesAuxilio(paramsAuxilio);

    QString paramsAhorro[2] = {maxTasaAhorro, minTasaAhorro};
    daofondo.ActualizarPropiedadesAhorro(paramsAhorro);
}

void FondoTrabajadores::on_bFaqActualizar_clicked()
{
    DAOFaq daoFaq;
    QList<QList<QString>> consulta = daoFaq.ConsultarFaq("Pendiente");

    ui->tFaq->setRowCount(consulta.length());
    for(int i=0; i<consulta.length(); i++){
        for(int j=0; j<4; j++){
            QString dato="";
            if (j==0){
                dato = consulta[i][0];
            }
            if (j==1){
                dato = consulta[i][1];
            }

            ui->tFaq->setItem(i, j, new QTableWidgetItem(dato));
        }
    }
}



void FondoTrabajadores::on_tabWidget_currentChanged(int index)
{
    if (index == 4){
        DAOFondo daofondo;

        QList<QString> listaFondo = daofondo.ConsultarFondo();
        ui->lOpcSmmlv->setText(listaFondo[1]);
        ui->lOpcIva->setText(listaFondo[2]);

        QList<QString> listaCredito = daofondo.ConsultarPropiedadesCredito();
        ui->lOpcMaxCuotas->setText(listaCredito[3]);
        ui->lOpcAntiguedad->setText(listaCredito[4]);
        ui->lOpcTasaCredito->setText(listaCredito[1]);
        ui->lOpcValorMax->setText(listaCredito[2]);
        ui->lOpcValorAdmin->setText(listaCredito[5]);
        ui->lOpcSeguro->setText(listaCredito[6]);
        ui->lOpcValorPlataforma->setText(listaCredito[7]);

        QList<QString> listaAuxilio = daofondo.ConsultarPropiedadesAuxilio();
        ui->lOpcTasaCalamidad->setText(listaAuxilio[1]);
        ui->lOpcTasaEdu->setText(listaAuxilio[2]);
        ui->lOpcMaxCalamidad->setText(listaAuxilio[3]);
        ui->lOpcMaxAux->setText(listaAuxilio[4]);

        QList<QString> listaAhorro = daofondo.ConsultarPropiedadesAhorro();
        qDebug() << listaAhorro.length();
        ui->lOpcMinTasaAhorro->setText(listaAhorro[2]);
        ui->lOpcMaxTasaAhorro->setText(listaAhorro[1]);
    }else if(index == 3){
        DAOFaq daoFaq;
        QList<QList<QString>> consulta = daoFaq.ConsultarFaq("Pendiente");

        ui->tFaq->setRowCount(consulta.length());
        for(int i=0; i<consulta.length(); i++){
            for(int j=0; j<4; j++){
                QString dato="";
                if (j==0){
                    dato = consulta[i][0];
                }
                if (j==1){
                    dato = consulta[i][1];
                }

                ui->tFaq->setItem(i, j, new QTableWidgetItem(dato));
            }
        }
    }
}

void FondoTrabajadores::on_bFaqResolver_clicked()
{
    if(ui->tFaq->isItemSelected(ui->tFaq->item(ui->tFaq->currentRow(),0))){
        int id = ui->tFaq->item(ui->tFaq->currentRow(),0)->text().toInt();
        QString pregunta = ui->tFaq->item(ui->tFaq->currentRow(),1)->text();

        ResolverPregunta *r = new ResolverPregunta(id, pregunta);
        r->show();
        qDebug() << ui->tFaq->item(ui->tFaq->currentRow(),0)->text();
    }else{
        QMessageBox::information(this, "Info", "Por favor seleccione una referencia");
    }
}
