#ifndef SINGLEMOTOR_H
#define SINGLEMOTOR_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <math.h>
#include "Box.h"
#include <QRectF>



class SingleMotor : public QObject
{
    Q_OBJECT

private:
    Box *box;
    My_action my_action;
    QTimer *timer;

    //служебные
    int count; // счётчик для управления
    int count_shot; //счётчик выстрелов
    int destroy_npc;//кол во уничтоженных танков
    void stepOnAngle(int &x, int &y, int angle, int step); //изменение х у на длину step по углу angle
    void initObjects();//инициализация объектов
    void gameOver();//конец игры

    //мой объект
    void stepObject(int &x, int &y, int angl, int step); // фуек вычисляет координаты точки шагов step
    void bendObject(int x, int y, int &angl,bool factor); // поворачивает ствол



    //боты
    void actionNPC(); //действия ботов(обёртка для функциий)
    void birthNPC(int c); //появление ботов
    void stepNPC(int c); //вычисляет и передвигает бота



    //выстрелы
    void birthShot(); //выстрел, образование патрона
    void stepShot();  //обработка выстрела, каждую еденицу времени

    //ограничения
    void limitAll(); //обёртка для всех ограничений(каждую ед вр)
    void hitInNpc(); //проверка на попадание в бота
    void destroyNpc(int shot); //уничтожение бота



public:
    explicit SingleMotor(QObject *parent = 0);
    void start(); //временный метод для старта движка





signals:
    void toMapping_sig(Box*); //сигнал отправляет на отображение класс Box
    void stopGame_sig();//конец игры

public slots:
    void myActionFromMapping_sl(My_action);//слот получающий действие моегго танка
    void repeatAction();//метод для действия через 0.1

};

#endif // SINGLEMOTOR_H
