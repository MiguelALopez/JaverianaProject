#ifndef ASOCIADOSFONDO_H
#define ASOCIADOSFONDO_H

#include <QMainWindow>

namespace Ui {
class AsociadosFondo;
}

class AsociadosFondo : public QMainWindow
{
    Q_OBJECT

public:
    explicit AsociadosFondo(QString cedula, QWidget *parent = 0);
    ~AsociadosFondo();

private slots:
    void on_bSalir_clicked();

    void on_bSimular_clicked();

    void on_bCredSolicitud_clicked();

    void on_bAuxSolicitud_clicked();

    void on_bAhoAdiccionar_clicked();

    void on_bCredConsulta_clicked();

    void on_bAuxConsulta_clicked();

    void on_bAhoConsulta_clicked();

    void on_bUserGuardar_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::AsociadosFondo *ui;

    QString cedula;
};

#endif // ASOCIADOSFONDO_H
