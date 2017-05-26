#include "fondotrabajadores.h"
#include "ui_fondotrabajadores.h"
#include <QIntValidator>

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
    int size;
    for(int i = 0; i < size; i++){
        int puntos = 0;

        QString cedula;
        double ingresos;
        double gastos;

        // Categoria 1
        double disponible = (ingresos - gastos) * 0.25;

        if(disponible > 1.5){
            puntos += 75;
        }else if(disponible > 1){
            puntos += 50;
        }

        // Categoria 2
        int cat2 = qrand() % 30;
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
        int cat3 = qrand() % 50;
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

        if(puntos >= 200){
            // Se aprueba el credito
        }else{
            // Se deniega el credito
        }
    }
}

void FondoTrabajadores::on_bSalir_clicked()
{
    close();
}

void FondoTrabajadores::on_bCredActualizar_clicked()
{
    QString inicial = ui->dateCredInicial->date().toString("yyyy-M-d");
    QString final = ui->dateCredFinal->date().toString("yyyy-M-d");

    int total = 0;

    int size;
    for(int i = 0; i < size; i++){
        QString fecha;
        QString nombre;
        QString apellido;
        QString monto;
        total += monto.toInt();

        ui->tCreditos->insertRow(ui->tCreditos->rowCount());
        ui->tCreditos->setItem(ui->tCreditos->rowCount() - 1, 0,
                               new QTableWidgetItem(fecha));
        ui->tCreditos->setItem(ui->tCreditos->rowCount() - 1, 1,
                               new QTableWidgetItem(nombre));
        ui->tCreditos->setItem(ui->tCreditos->rowCount() - 1, 2,
                               new QTableWidgetItem(apellido));
        ui->tCreditos->setItem(ui->tCreditos->rowCount() - 1, 3,
                               new QTableWidgetItem(monto));
    }

    ui->lCredValorTotal->setText(QString::number(total));
    ui->lCredNumTotal->setText(QString::number(size));
}

void FondoTrabajadores::on_bAuxActualizar_clicked()
{
    QString inicial = ui->dateAuxInit->date().toString("yyyy-M-d");
    QString final = ui->dateAuxFinal->date().toString("yyyy-M-d");

    int total = 0;

    int size;
    for(int i = 0; i < size; i++){
        QString fecha;
        QString nombre;
        QString apellido;
        QString tipo;
        QString monto;
        total += monto.toInt();

        ui->tAuxilio->insertRow(ui->tAuxilio->rowCount());
        ui->tAuxilio->setItem(ui->tAuxilio->rowCount() - 1, 0,
                               new QTableWidgetItem(fecha));
        ui->tAuxilio->setItem(ui->tAuxilio->rowCount() - 1, 1,
                               new QTableWidgetItem(nombre));
        ui->tAuxilio->setItem(ui->tAuxilio->rowCount() - 1, 2,
                               new QTableWidgetItem(apellido));
        ui->tAuxilio->setItem(ui->tAuxilio->rowCount() - 1, 3,
                               new QTableWidgetItem(tipo));
        ui->tAuxilio->setItem(ui->tAuxilio->rowCount() - 1, 4,
                               new QTableWidgetItem(monto));
    }

    ui->lAuxValorTotal->setText(QString::number(total));
    ui->lAuxNumTotal->setText(QString::number(size));
}

void FondoTrabajadores::on_bAhoActualizar_clicked()
{
    QString inicial = ui->dateAhoInit->date().toString("yyyy-M-d");
    QString final = ui->dateAhoFinal->date().toString("yyyy-M-d");

    int total = 0;

    int size;
    for(int i = 0; i < size; i++){
        QString fecha;
        QString nombre;
        QString apellido;
        QString monto;
        total += monto.toInt();

        ui->tAhorro->insertRow(ui->tAhorro->rowCount());
        ui->tAhorro->setItem(ui->tAhorro->rowCount() - 1, 0,
                               new QTableWidgetItem(fecha));
        ui->tAhorro->setItem(ui->tAhorro->rowCount() - 1, 1,
                               new QTableWidgetItem(nombre));
        ui->tAhorro->setItem(ui->tAhorro->rowCount() - 1, 2,
                               new QTableWidgetItem(apellido));
        ui->tAhorro->setItem(ui->tAhorro->rowCount() - 1, 3,
                               new QTableWidgetItem(monto));
    }

    ui->lAhoValorTotal->setText(QString::number(total));
    ui->lAhoNumTotal->setText(QString::number(size));
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
}

void FondoTrabajadores::on_bFaqActualizar_clicked()
{
    int size;
    for(int i = 0; i < size; i++){
        QString titulo;
        QString descripcion;

        ui->tAhorro->insertRow(ui->tAhorro->rowCount());
        ui->tAhorro->setItem(ui->tAhorro->rowCount() - 1, 0,
                               new QTableWidgetItem(titulo));
        ui->tAhorro->setItem(ui->tAhorro->rowCount() - 1, 1,
                               new QTableWidgetItem(descripcion));
    }
}
