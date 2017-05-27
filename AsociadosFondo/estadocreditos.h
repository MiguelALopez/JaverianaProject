#ifndef ESTADOCREDITOS_H
#define ESTADOCREDITOS_H

#include <QWidget>

namespace Ui {
class EstadoCreditos;
}

class EstadoCreditos : public QWidget
{
    Q_OBJECT

public:
    explicit EstadoCreditos(QString cedula, QWidget *parent = 0);
    ~EstadoCreditos();


private slots:
    void on_bActualizar_clicked();

private:
    Ui::EstadoCreditos *ui;
    QString cedula;
};

#endif // ESTADOCREDITOS_H
