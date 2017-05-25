#include "registrar.h"
#include "ui_registrar.h"

Registrar::Registrar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registrar)
{
    ui->setupUi(this);
}

Registrar::~Registrar()
{
    delete ui;
}
