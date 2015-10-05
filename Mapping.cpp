#include "Mapping.h"

void Mapping::drawMy(QPainter *p)
{

    p->setPen(QPen(Qt::black,1,Qt::SolidLine));
    p->drawEllipse(QPoint(box->my.x, box->my.y) , box->my.h, box->my.h);
    p->drawLine(box->my.x , box->my.y, box->my.x_a,box->my.y_a);// box->my.x - 40*cos(Pi/180*box->my.angle),box->my.y - 40*sin(Pi/180*box->my.angle));
    //p->drawRect(box->my.x - box->my.h, box->my.y - box->my.h, box->my.h*2, box->my.h*2);
}

void Mapping::drawNPC(QPainter *p)
{
    //p->setPen(QPen(Qt::black,1,Qt::SolidLine));
    for(int i = 0; i < box->MAX_NPC; i++)
    {
        if(box->npc[i].active == true)
        p->drawEllipse(QPoint(box->npc[i].x, box->npc[i].y) ,box->npc[i].h , box->npc[i].h);
       // p->drawRect(box->npc[i].x - box->npc[i].h/2, box->npc[i].y - box->npc[i].h/2, box->npc[i].h, box->npc[i].h);

    }

}

void Mapping::drawShot(QPainter *p)
{
    for(int i = 0; i <= MAX_SHOTS; i++)
    {
        if(box->shot[i].active == true)
            p->drawEllipse(QPoint(box->shot[i].x, box->shot[i].y) ,box->shot[i].h , box->shot[i].h);

    }

}

void Mapping::showInfo()
{



    switch(box->my.type_weapon)
    {
    case 1:
        my_weapon->setText("weapon: SMIT");
        repaint();
        break;

    case 2:
        my_weapon->setText("weapon: UZI");
        repaint();
        break;

    case 3:
        my_weapon->setText("weapon: SHOTGUN");
        repaint();
        break;

    case 4:
        my_weapon->setText("weapon: T-34");
        break;

    }
    QString str("level: ");
    QString num;
    num.setNum(box->level);
    str += num;
    //str.setNum(box->level);
    level->setText(static_cast<const QString>(str));
    //level->setNum(box->level);
    str = "score: ";
    num.setNum(box->score);
    str += num;
    score->setText(static_cast<const QString>(str));

    str = "health: ";
    num.setNum(box->my.health);
    str += num;
    health->setText(static_cast<const QString>(str));



}

Mapping::Mapping(QWidget *parent) :
    QWidget(parent)
{
    box = new Box;
    /*box->my.x = 500;
    box->my.y = 500;
    box->my.h = 50;
    box->my.r = 0;
    box->my.angle = 0;*/
    my_weapon = new QLabel(this);
    my_weapon->setGeometry(25,545,200,30);
    my_weapon->show();
    level = new QLabel("level",this);
    level->setGeometry(225,545,200,30);
    level->show();
    health = new QLabel(this);
    health->setGeometry(25,570,200,30);
    score = new QLabel("score",this);
    score->setGeometry(225,570,200,30);


    resize(WIDGET_W,WIDGET_H);

    //show();
}

void Mapping::paintEvent(QPaintEvent *event)
{

    QPainter p(this);
    p.drawRect(10,10,WIDGET_W - 20, WIDGET_H - 60);

    drawMy(&p);
    drawNPC(&p);
    drawShot(&p);
    p.end();
}

void Mapping::keyPressEvent(QKeyEvent *ev)
{

    switch(ev->key())
    {
    case Qt::Key_Up:
        my_action = UP;
        emit myActionToMotor_sig(my_action);
        break;

    case Qt::Key_Down:
        my_action = DOWN;
        emit myActionToMotor_sig(my_action);
        break;

    case Qt::Key_Left:
        my_action = LEFT;
        emit myActionToMotor_sig(my_action);
        break;

    case Qt::Key_Right:
        my_action = RIGHT;
        emit myActionToMotor_sig(my_action);
        break;

    case Qt::Key_Space:
        my_action = SHOT;
        emit myActionToMotor_sig(my_action);
        break;

    case Qt::Key_Control:
        my_action = CHANGE_WEAPON;
        emit myActionToMotor_sig(my_action);
        break;
    }
}

void Mapping::recvMotor_sl(Box *b)
{

    box = b;
    //qDebug() << " x y" << box->my.x << box->my.y;
    //qDebug() << " xa ya" << box->my.x_a << box->my.y_a;
    //qDebug() << " angle " << box->my.angle;
    //qDebug() << "angle npc\n" << box->npc[1].angle;
    //qDebug() << "angle npc 2" << box->npc[2].angle;
    //qDebug() << "x y shot" << box->shot[0].x << box->shot[0].y;
    showInfo();
    repaint();
}
