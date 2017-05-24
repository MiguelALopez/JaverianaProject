#include "fondotrabajadores.h"
#include "ui_fondotrabajadores.h"

FondoTrabajadores::FondoTrabajadores(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FondoTrabajadores)
{
    ui->setupUi(this);
}

FondoTrabajadores::~FondoTrabajadores()
{
    delete ui;
}
