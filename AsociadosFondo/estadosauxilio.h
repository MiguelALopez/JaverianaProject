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
    explicit EstadosAuxilio(QWidget *parent = 0);
    ~EstadosAuxilio();

private:
    Ui::EstadosAuxilio *ui;
};

#endif // ESTADOSAUXILIO_H
