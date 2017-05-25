#include "estadosauxilio.h"
#include "ui_estadosauxilio.h"

EstadosAuxilio::EstadosAuxilio(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EstadosAuxilio)
{
    ui->setupUi(this);
}

EstadosAuxilio::~EstadosAuxilio()
{
    delete ui;
}
