#include "validador.h"
#include "QMessageBox"

Validador::Validador()
{

}
bool Validador::validarUsuario(QString nombre, QString apellido, QString cedula, QString password, QString telefono,
                               QString direccion, QString sexo, QString estado, QString correo, QString ingresos, QWidget *window){
    bool valido = true;

    if(nombre == ""){
        QMessageBox::information(window, "Error","Debe ingresar un nombre");
        valido = false;
    }

    if(apellido == ""){
        QMessageBox::information(window, "Error","Debe ingresar un apellido");
        valido = false;
    }

    if(password == ""){
        QMessageBox::information(window, "Error","Debe ingresar una contraseña");
        valido = false;
    }

    if(direccion== ""){
        QMessageBox::information(window, "Error","Debe ingresar una dirección");
        valido = false;
    }

    if(sexo == ""){
        QMessageBox::information(window, "Error","Debe ingresar un sexo");
        valido = false;
    }

    if(estado == ""){
        QMessageBox::information(window, "Error","Debe ingresar un estado civil");
        valido = false;
    }

    if(!cedula.toDouble()){
        QMessageBox::information(window, "Error","La cedula solo debe contener numeros");
        valido = false;
    }

    if(!telefono.toDouble()){
        QMessageBox::information(window, "Error","EL telefono solo debe contener numeros");
        valido = false;
    }

    if(!correo.contains("@")){
        QMessageBox::information(window, "Error","El correo electronico no es valido");
        valido = false;
    }

    if(!ingresos.toDouble()){
        QMessageBox::information(window, "Error","Los ingresos deben ser numericos");
        valido = false;
    }
    if(ingresos.toDouble() && ingresos > 10000000){
        QMessageBox::information(window, "Error","Los ingresos deben ser menores a 10 millones");
        valido = false;
    }


    return valido;
}

