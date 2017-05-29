#ifndef ESTADOSAUXILIO_H
#define ESTADOSAUXILIO_H

#include <QWidget>

namespace Ui {
class EstadosAuxilio;
}

class EstadosAuxilio : public QWidget
{
    Q_OBJECT

public:
    explicit EstadosAuxilio(QString cedula, QWidget *parent = 0);
    ~EstadosAuxilio();

private slots:
    void on_bActualizar_clicked();

    void on_bCerrar_clicked();

private:
    Ui::EstadosAuxilio *ui;
    QString cedula;
};

#endif // ESTADOSAUXILIO_H
