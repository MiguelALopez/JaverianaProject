#ifndef VALIDADOR_H
#define VALIDADOR_H

#include <QString>
#include <QWidget>

class Validador
{
public:
    Validador();
    bool validarUsuario(QString nombre, QString apellido, QString cedula, QString password, QString telefono,
                        QString direccion, QString sexo, QString estado, QString correo, QString ingresos, QWidget *window);
};

#endif // VALIDADOR_H
