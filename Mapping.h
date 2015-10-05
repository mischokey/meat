#ifndef MAPPING_H
#define MAPPING_H

#include <QWidget>
//#include <QPainter>
#include <QPaintEvent>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <QEvent>
#include <QLabel>
#include <math.h>
#include "Box.h"


#define WIDGET_H 600
#define WIDGET_W 800
#define Pi 3.14159265359

class Mapping : public QWidget
{
    Q_OBJECT

private:
    Box *box;
    My_action my_action;

    QLabel *my_weapon;
    QLabel *level;
    QLabel *score;
    QLabel *health;

    void drawMy(QPainter*); //прорисовка моего объекта
    void drawNPC(QPainter*); //прорисовка ботов
    void drawShot(QPainter*); //прорисовка патронов

    void showInfo();
public:
    Mapping(QWidget *parent = 0);
    //~Mapping();

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *);
signals:
    void myActionToMotor_sig(My_action); //отправить на движок действие моего танка

public slots:
    void recvMotor_sl(Box*);  //получение структуры бокс от движка
};

#endif // MAPPING_H







