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

private:
    Ui::FondoTrabajadores *ui;
};

#endif // FONDOTRABAJADORES_H
