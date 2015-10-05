#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>

#include "Mapping.h"
#include "SingleMotor.h"

class Dialog : public QDialog
{
    Q_OBJECT
private:
    Mapping *mapping;
    SingleMotor *single_motor;
    QWidget *w;

    void showMenu(bool);
public:
    Dialog(QWidget *parent = 0);

    QPushButton *single_game;
    ~Dialog();

public slots:
    void singleGame_sl();
};

#endif // DIALOG_H
