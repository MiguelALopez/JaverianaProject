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
    explicit EstadoAhorro(QWidget *parent = 0);
    ~EstadoAhorro();

private:
    Ui::EstadoAhorro *ui;
};

#endif // ESTADOAHORRO_H
