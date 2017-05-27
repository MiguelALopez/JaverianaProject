#ifndef PREGUNTA_H
#define PREGUNTA_H

#include <QWidget>

namespace Ui {
class Pregunta;
}

class Pregunta : public QWidget
{
    Q_OBJECT

public:
    explicit Pregunta(QString cedula, QWidget *parent = 0);
    ~Pregunta();

private slots:
    void on_bCancelar_clicked();

    void on_bGuardar_clicked();

private:
    Ui::Pregunta *ui;
    QString cedula;
};

#endif // PREGUNTA_H
