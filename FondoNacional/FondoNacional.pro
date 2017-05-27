#-------------------------------------------------
#
# Project created by QtCreator 2017-05-23T19:11:50
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FondoNacional
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += console
CONFIG -= app_bundle

SOURCES += main.cpp\
        fondotrabajadores.cpp \
    connection.cpp \
    daoahorro.cpp \
    daoauxilio.cpp \
    daofaq.cpp \
    daofondo.cpp \
    daonotificacion.cpp \
    daousuario.cpp \
    daocredito.cpp \
    resolverpregunta.cpp

HEADERS  += fondotrabajadores.h \
    connection.h \
    daoahorro.h \
    daoauxilio.h \
    daofaq.h \
    daofondo.h \
    daonotificacion.h \
    daousuario.h \
    daocredito.h \
    resolverpregunta.h

FORMS    += fondotrabajadores.ui \
    resolverpregunta.ui
