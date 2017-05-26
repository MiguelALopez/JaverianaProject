#include "validador.h"
#include "QMessageBox"

Validador::Validador()
{

}

bool Validador::validarUsuario(QString cedula, QString telefono, QString correo, QString ingresos, QWidget *window){
    bool valido = true;

    if(!cedula.toInt()){
        QMessageBox::information(window, "Error","La cedula solo debe contener numeros");
        valido = false;
    }

    if(!telefono.toInt()){
        QMessageBox::information(window, "Error","EL telefono solo debe contener numeros");
        valido = false;
    }

    if(!correo.contains("@")){
        QMessageBox::information(window, "Error","El correo electronico no es valido");
        valido = false;
    }

    if(!ingresos.toInt()){
        QMessageBox::information(window, "Error","Los ingresos deben ser numericos");
        valido = false;
    }


    return valido;
}

