#ifndef RESOLVERPREGUNTA_H
#define RESOLVERPREGUNTA_H

#include <QWidget>

namespace Ui {
class ResolverPregunta;
}

class ResolverPregunta : public QWidget
{
    Q_OBJECT

public:
    explicit ResolverPregunta(int id, QString pregunta, QWidget *parent = 0);
    ~ResolverPregunta();

private slots:
    void on_bSalir_clicked();

    void on_bGuardar_clicked();

private:
    Ui::ResolverPregunta *ui;

    int id;
    QString pregunta;
};

#endif // RESOLVERPREGUNTA_H
