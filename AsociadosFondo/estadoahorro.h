#ifndef ESTADOAHORRO_H
#define ESTADOAHORRO_H

#include <QWidget>

namespace Ui {
class EstadoAhorro;
}

class EstadoAhorro : public QWidget
{
    Q_OBJECT

public:
    explicit EstadoAhorro(QString cedula, QWidget *parent = 0);
    ~EstadoAhorro();

private slots:
    void on_bActualizar_clicked();

private:
    Ui::EstadoAhorro *ui;
    QString cedula;
};

#endif // ESTADOAHORRO_H
