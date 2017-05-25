#include "estadocreditos.h"
#include "ui_estadocreditos.h"

EstadoCreditos::EstadoCreditos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EstadoCreditos)
{
    ui->setupUi(this);
}

EstadoCreditos::~EstadoCreditos()
{
    delete ui;
}
