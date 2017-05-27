#ifndef FONDOTRABAJADORES_H
#define FONDOTRABAJADORES_H

#include <QMainWindow>

namespace Ui {
class FondoTrabajadores;
}

class FondoTrabajadores : public QMainWindow
{
    Q_OBJECT

public:
    explicit FondoTrabajadores(QWidget *parent = 0);
    ~FondoTrabajadores();

private slots:
    void on_bCredAceptar_clicked();

    void on_bSalir_clicked();

    void on_bCredActualizar_clicked();

    void on_bAuxActualizar_clicked();

    void on_bAhoActualizar_clicked();

    void on_bOpcGuardar_clicked();

    void on_bFaqActualizar_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::FondoTrabajadores *ui;
};

#endif // FONDOTRABAJADORES_H
