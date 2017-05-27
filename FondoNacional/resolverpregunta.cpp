#include "resolverpregunta.h"
#include "ui_resolverpregunta.h"
#include "daofaq.h"
#include <QMessageBox>

ResolverPregunta::ResolverPregunta(int id, QString pregunta, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResolverPregunta)
{
    ui->setupUi(this);

    this->id = id;
    this->pregunta = pregunta;

    ui->lPregunta->setText(pregunta);

}

ResolverPregunta::~ResolverPregunta()
{
    delete ui;
}

void ResolverPregunta::on_bSalir_clicked()
{
    close();
}

void ResolverPregunta::on_bGuardar_clicked()
{
    QString respuesta = ui->teRespuesta->toPlainText();

    DAOFaq daoFaq;
    daoFaq.ActualizarFaq(QString::number(id), respuesta, "Resuelta");

    QMessageBox::information(this, "Exito","La respuesta fue almacenada con exito");
    close();
}
