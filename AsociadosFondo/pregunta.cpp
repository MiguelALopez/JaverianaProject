#include "pregunta.h"
#include "ui_pregunta.h"
#include "daofaq.h"
#include <QMessageBox>

Pregunta::Pregunta(QString cedula, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pregunta)
{
    ui->setupUi(this);
    this->cedula = cedula;
}

Pregunta::~Pregunta()
{
    delete ui;
}

void Pregunta::on_bCancelar_clicked()
{
    close();
}

void Pregunta::on_bGuardar_clicked()
{
    QString pregunta = ui->tPregunta->toPlainText();

    QString params[4];
    params[0] = pregunta;
    params[1] = "Pendiente";
    params[2] = cedula;

    DAOFaq daoFaq;
    daoFaq.CrearFaq(params);

    QMessageBox::information(this, "Exito","La pregunta fue registrada con exito");
    close();
}
