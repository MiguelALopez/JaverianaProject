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
    explicit AsociadosFondo(QWidget *parent = 0);
    ~AsociadosFondo();

private:
    Ui::AsociadosFondo *ui;
};

#endif // ASOCIADOSFONDO_H
