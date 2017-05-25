#include "estadoahorro.h"
#include "ui_estadoahorro.h"

EstadoAhorro::EstadoAhorro(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EstadoAhorro)
{
    ui->setupUi(this);
}

EstadoAhorro::~EstadoAhorro()
{
    delete ui;
}
