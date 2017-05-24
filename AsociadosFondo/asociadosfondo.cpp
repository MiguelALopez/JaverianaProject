#include "asociadosfondo.h"
#include "ui_asociadosfondo.h"

AsociadosFondo::AsociadosFondo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AsociadosFondo)
{
    ui->setupUi(this);
}

AsociadosFondo::~AsociadosFondo()
{
    delete ui;
}
