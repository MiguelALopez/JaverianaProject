#ifndef VALIDADOR_H
#define VALIDADOR_H

#include <QString>
#include <QWidget>

class Validador
{
public:
    Validador();
    bool validarUsuario(QString cedula, QString telefono, QString correo, QString ingresos, QWidget *window);
};

#endif // VALIDADOR_H
