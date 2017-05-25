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
    explicit EstadoCreditos(QWidget *parent = 0);
    ~EstadoCreditos();

private:
    Ui::EstadoCreditos *ui;
};

#endif // ESTADOCREDITOS_H
