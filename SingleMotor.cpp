#include "SingleMotor.h"

void SingleMotor::repeatAction()
{
   //gameOver();
    actionNPC();
     limitAll();
    stepShot();


    emit toMapping_sig(box);
}

void SingleMotor::stepOnAngle(int &x, int &y, int angle, int step)
{
    int a , b;
    a = x + step*cos(angle*Pi/180);
    b = y + step*sin(angle*Pi/180);

    if(a > (10 + box->my.h) && a < (790 - box->my.h)
            && b > (10 + box->my.h) && b < (550 - box->my.h) ) //ограничение на выход объекта за поле боя
    {
        x = a;
        y = b;
    }

}

void SingleMotor::initObjects()
{
    box = new Box;
    box->MAX_NPC = 15;
    box->level = 1;
    count = 0;
    count_shot = 0;
    destroy_npc = 0;
    box->score = 0;

    for(int i = 0; i < box->MAX_NPC; i++)
    {
        box->npc[i].x = 0;
        box->npc[i].y = 0;
        box->npc[i].h = 0;
        box->npc[i].r = 0;
        box->npc[i].angle = 0;
        box->npc[i].active = false;


    }

    for(int i = 0; i < MAX_SHOTS; i++)
    {
        box->shot[i].x = 0;
        box->shot[i].y = 0;
        box->shot[i].h = 0;
        box->shot[i].r = 0;
        box->shot[i].angle = 0;

    }


    box->my.x = 400;
    box->my.y = 300;
    box->my.h = 25;
    box->my.r = 25;
    box->my.angle = 90;
    box->my.x_a = 200;
    box->my.y_a = 260;
    box->my.type_weapon = 1;
    box->my.health = 100;

}

void SingleMotor::gameOver()
{

    if(box->my.health == 0)
    {
        qDebug() << "end game";
        timer->stop();
        //emit stopGame_sig();
    }

}

void SingleMotor::stepObject(int &x, int &y, int angl, int step)
{
    int factor;
   /* if((angl > 180) && (angl <= 360))
        factor = 1;


    if((angl >= 0) && (angl <= 180))*/
        factor = -1;

    //x = x + step*cos(angl*Pi/180);
    //y = y + step*sin(angl*Pi/180);
        /*if(step > 0)
        {    box->my.angle += 180;
            step = step * factor;
        }*/

    stepOnAngle(x,y,angl,step);
    box->my.x_a = box->my.x + (40*cos(Pi/180*box->my.angle)*factor);
    box->my.y_a = box->my.y + (40*sin(Pi/180*box->my.angle)*factor);

}

void SingleMotor::bendObject(int x, int y, int &angl, bool factor)
{

    int f;


    if(factor == true)
        angl -= 4;

    if(factor == false)
        angl += 4;

    /*if((angl > 180) && (angl <= 360))
        f = 1;


    if((angl >= 0) && (angl <= 180))*/
        f = -1;


    box->my.x_a = x + (40*cos(Pi/180*angl)*f);
    box->my.y_a = y + (40*sin(Pi/180*angl)*f);

    if(factor == true && angl == 0)
        angl = 360;

    if(factor == false && angl == 360)
        angl = 0;

}

void SingleMotor::actionNPC()
{
    count++;
    birthNPC(count);
    stepNPC(count);

}

void SingleMotor::birthNPC(int c)
{
    if(destroy_npc == (box->MAX_NPC - 1))
    {
        qDebug() << "next level";
        box->level++;
        box->MAX_NPC+= 20;
        destroy_npc = 0;
        count = 0;
        return;
    }
    int i;
    if(c/10 == box->MAX_NPC || c/10 >= box->MAX_NPC)
        return;
    if(c % 10 == 0)
        i = c / 10;
    else
        return;
    int ran = rand() % 2;
    qDebug() << "ran" << ran << "i" << i;
    switch(ran)
    {
    case 0:
        box->npc[i].x = 400;
        box->npc[i].y = 30;
        box->npc[i].h = 20;
        box->npc[i].r = 30;
        box->npc[i].angle = 270;
        box->npc[i].active = true;


        break;

    case 1:
        box->npc[i].x = 400;
        box->npc[i].y = 530;
        box->npc[i].h = 20;
        box->npc[i].r = 25;
        box->npc[i].angle = 110;
        box->npc[i].active = true;

        break;
    }
}

void SingleMotor::stepNPC(int c)
{


    if(c % 5 != 0)
        return;
    double r;
    for(int i = 0; i < box->MAX_NPC; i++)
    {
        if(box->npc[i].active == true)
        {
            r = sqrt(pow((box->my.x - box->npc[i].x),2) + pow((box->my.y - box->npc[i].y),2));
            //int r ;
            //r = (int)rad;
            //qDebug() << "r" << r;
           /*if(box->my.x < box->npc[i].x)
                box->npc[i].angle = 360 - 180/Pi *acos((box->my.x - box->npc[i].x)/r);
           if (box->my.y > box->npc[i].y)
                box->npc[i].angle = 180/Pi *acos((box->my.x - box->npc[i].x)/r);*/

            int x , y;
            /*if(box->my.x < box->npc[i].x && box->my.y < box->npc[i].y) // первая четверь относительно бота
            {
                x = box->my.x - box->npc[i].x;
                y = box->npc[i].y - box->my.y;
                box->npc[i].angle = 180/Pi *acos(x/r);
               // qDebug() << box->npc[2].angle << "angle cos";

            }*/
            double angle;

            angle = 180/Pi *acos((box->my.x - box->npc[i].x)/r);
            //qDebug() << angle << "             angle          ";
            if(box->my.y < box->npc[i].y)
                box->npc[i].angle = 180 - 180/Pi *acos((box->my.x - box->npc[i].x)/r);

            if(box->my.y > box->npc[i].y)
                box->npc[i].angle = 180 + 180/Pi *acos((box->my.x - box->npc[i].x)/r);


            //box->npc[2].angle = (int)angle;
             //qDebug() << box->npc[2].angle << "angle int";
           //qDebug() << "angle" << box->npc[2].angle;

            x = box->npc[i].x + STEP_NPC*cos(box->npc[i].angle*Pi/180)*-1;
            y = box->npc[i].y + STEP_NPC*sin(box->npc[i].angle*Pi/180)*-1;

            if((QRect(x - box->npc[i].h, y - box->npc[i].h, box->npc[i].h*2, box->npc[i].h*2))
                    .intersects(QRect(box->my.x - box->my.h, box->my.y - box->my.h, box->my.h*2, box->my.h*2)))
            {
                box->my.health -= 10;
                qDebug() << "my health" << box->my.health;
                gameOver();
                //break;
            }
            else
            {
                box->npc[i].x = x;
                box->npc[i].y = y;

            /*for(int iii = 0; iii < box->MAX_NPC; iii++)
            {
                if(box->npc[iii].active == true)
                {
                    if((QRect(x - box->npc[i].h, y - box->npc[i].h, box->npc[i].h*2, box->npc[i].h*2))
                            .intersects(QRect(box->npc[iii].x - box->npc[iii].h, box->npc[iii].y - box->npc[iii].h,
                                              box->npc[iii].h*2, box->npc[iii].h*2)))
                    {
                        if(iii == i)
                        {
                            qDebug() << "end";
                            break;
                        }
                        qDebug() << "crash";
                        box->npc[i].x = box->npc[i].x;
                        box->npc[i].y = box->npc[i].y;
                    }
                    else
                    {
                        box->npc[i].x = x;
                        box->npc[i].y = y;
                    }
                }
            }*/
            }

        }
    }



}

void SingleMotor::birthShot()
{

    if(count_shot >= 50)
        count_shot = 0;
    qDebug() << "birth" << count_shot;
    switch(box->my.type_weapon)
    {
    case 1: //обычный выстрел
        box->shot[count_shot].x = box->my.x_a;
        box->shot[count_shot].y = box->my.y_a;
        box->shot[count_shot].type = box->my.type_weapon;
        box->shot[count_shot].angle = box->my.angle;
        box->shot[count_shot].active = true;
        box->shot[count_shot].h = box->shot[count_shot].type*2;
        box->shot[count_shot].x_end = box->shot[count_shot].x - (100*cos(Pi/180*box->shot[count_shot].angle));
        box->shot[count_shot].y_end = box->shot[count_shot].y - (100*sin(Pi/180*box->shot[count_shot].angle));

        //qDebug() << box->shot[count_shot].x_end << " x end";
        //qDebug() << box->shot[count_shot].y_end << "y end";
        count_shot ++;
        break;
    case 2: //выстрел узи
        for(int i = 0; i <= 4; i++)
        {
            box->shot[count_shot].angle = box->my.angle;
            box->shot[count_shot].x = box->my.x_a + i*10*cos(Pi/180*box->shot[count_shot].angle);
            box->shot[count_shot].y = box->my.y_a + i*10*sin(Pi/180*box->shot[count_shot].angle);
            box->shot[count_shot].type = box->my.type_weapon;
            box->shot[count_shot].angle = box->my.angle;
            box->shot[count_shot].active = true;
            box->shot[count_shot].h = 2;

            box->shot[count_shot].x_end = box->shot[count_shot].x - (100*cos(Pi/180*box->shot[count_shot].angle));
            box->shot[count_shot].y_end = box->shot[count_shot].y - (100*sin(Pi/180*box->shot[count_shot].angle));


            count_shot++;
            if(count_shot >= 50)
                count_shot = 0;
        }
        //count_shot += 5;
        break;
    case 3: //выстрел дробовик
        for(int i = 0; i <= 8; i++)
        {
            box->shot[count_shot].angle = box->my.angle;
            if(i == 0)
            {
                box->shot[count_shot].x = box->my.x_a + i*20*cos(Pi/180*box->shot[count_shot].angle);
                box->shot[count_shot].y = box->my.y_a + i*20*sin(Pi/180*box->shot[count_shot].angle);
            }
            if(i == 1)
            {
                box->shot[count_shot].x = box->my.x_a + 20*cos(Pi/180*(box->shot[count_shot].angle + 35));
                box->shot[count_shot].y = box->my.y_a + 20*sin(Pi/180*(box->shot[count_shot].angle + 35));
            }

            if(i == 2)
            {
                box->shot[count_shot].x = box->my.x_a + 20*cos(Pi/180*(box->shot[count_shot].angle - 20));
                box->shot[count_shot].y = box->my.y_a + 20*sin(Pi/180*(box->shot[count_shot].angle - 20));
            }

            if(i == 3)
            {
                box->shot[count_shot].x = box->my.x_a + 40*cos(Pi/180*(box->shot[count_shot].angle + 80));
                box->shot[count_shot].y = box->my.y_a + 40*sin(Pi/180*(box->shot[count_shot].angle + 80));
            }

            if(i == 4)
            {
                box->shot[count_shot].x = box->my.x_a + 40*cos(Pi/180*(box->shot[count_shot].angle - 75));
                box->shot[count_shot].y = box->my.y_a + 40*sin(Pi/180*(box->shot[count_shot].angle - 75));
            }

            if(i == 5)
            {
                box->shot[count_shot].x = box->my.x_a + 40*cos(Pi/180*(box->shot[count_shot].angle));
                box->shot[count_shot].y = box->my.y_a + 40*sin(Pi/180*(box->shot[count_shot].angle));
            }

            if(i == 6)
            {
                box->shot[count_shot].x = box->my.x_a + 60*cos(Pi/180*(box->shot[count_shot].angle + 50));
                box->shot[count_shot].y = box->my.y_a + 60*sin(Pi/180*(box->shot[count_shot].angle + 50));
            }

            if(i == 7)
            {
                box->shot[count_shot].x = box->my.x_a + 60*cos(Pi/180*(box->shot[count_shot].angle - 50));
                box->shot[count_shot].y = box->my.y_a + 60*sin(Pi/180*(box->shot[count_shot].angle - 50));
            }

            if(i == 8)
            {
                box->shot[count_shot].x = box->my.x_a + 70*cos(Pi/180*(box->shot[count_shot].angle));
                box->shot[count_shot].y = box->my.y_a + 70*sin(Pi/180*(box->shot[count_shot].angle));
            }
            box->shot[count_shot].type = box->my.type_weapon;
            box->shot[count_shot].active = true;
            box->shot[count_shot].h = 2;

            box->shot[count_shot].x_end = box->shot[count_shot].x - (100*cos(Pi/180*box->shot[count_shot].angle));
            box->shot[count_shot].y_end = box->shot[count_shot].y - (100*sin(Pi/180*box->shot[count_shot].angle));
            count_shot++;
            if(count_shot >= 50)
                count_shot = 0;
        }
        //count_shot += 9;
        break;

    case 4: // выстрел T-34
        box->shot[count_shot].x = box->my.x_a;
        box->shot[count_shot].y = box->my.y_a;
        box->shot[count_shot].type = box->my.type_weapon;
        box->shot[count_shot].angle = box->my.angle;
        box->shot[count_shot].active = true;
        box->shot[count_shot].h = 7;
        box->shot[count_shot].x_end = box->shot[count_shot].x - (100*cos(Pi/180*box->shot[count_shot].angle));
        box->shot[count_shot].y_end = box->shot[count_shot].y - (100*sin(Pi/180*box->shot[count_shot].angle));

        count_shot ++;

        break;
    }

    /*for(int i = 0; i <= 4; i ++)
    {
        qDebug() << box->shot[i].x << "x " << i;
        qDebug() << box->shot[i].y << "y " << i;
        qDebug() << box->shot[i].type << "type " << i;
        qDebug() << box->shot[i].angle << "angle " << i;
        qDebug() << box->shot[i].active << "active " << i;
        qDebug() << box->shot[i].h << "h " << i;
        qDebug() << box->shot[i].x_end << "x_end " << i;
        qDebug() << box->shot[i].y_end << "y_end " << i;
        qDebug() << "\n\n\n\n ";
    }*/

}

void SingleMotor::stepShot()
{

    for(int i = 0; i < 50; i++)
    {

        if(box->shot[i].active == true)
        {
            /*if(box->shot[count_shot].x + 100 >= box->shot[count_shot].x_end &&
                    box->shot[count_shot].y + 100 >=box->shot[count_shot].y_end)
            {
                box->shot[count_shot].active = false;
                qDebug() << "shot out range";
                return;
            }*/
            //qDebug() << "shot step";
            int factor;
            factor = -1;
            /* if(box->shot[i].angle > 0 && box->shot[i].angle < 180)
                factor = -1;
            if(box->shot[i].angle > 180 && box->shot[i].angle < 360)
                factor = 1;*/
            int a , b;
            a = box->shot[i].x + factor*STEP_SHOT*cos(Pi/180*box->shot[i].angle);
            b = box->shot[i].y + factor*STEP_SHOT*sin(Pi/180*box->shot[i].angle);

            if(a > 10  && a < 790
                    && b > 10  && b < 550) // если выстрел выходит за пределы зоны
            {
                box->shot[i].x = a;
                box->shot[i].y = b;
            }
            else
            {
                box->shot[i].active = false;

            }
        }
    }
}

void SingleMotor::limitAll()
{
    hitInNpc();

}

void SingleMotor::hitInNpc()
{
    for(int i = 0; i < MAX_SHOTS; i++)
    {
        if(box->shot[i].active == true)
        {
            destroyNpc(i);
        }

    }

}

void SingleMotor::destroyNpc(int shot)
{
    int i = shot;
    for(int iii = 0; iii < 11; iii++)
    {


        int a, b;
        if(iii == 0)
        {
            a = box->shot[i].x;
            b = box->shot[i].y;
        }
        else
        {
        a = a  - 10*cos(Pi/180*box->shot[i].angle);
        b = b  - 10*sin(Pi/180*box->shot[i].angle);
        }
        for(int j = 0; j < box->MAX_NPC; j++)
        {
            if(box->npc[j].active == true)
            {
                if(box->shot[i].type == 4) //поподание т34
                {
                    if((QRect(a - box->shot[i].h, b - box->shot[i].h, box->shot[i].h*2, box->shot[i].h*2))
                            .intersects(QRect(box->npc[j].x - box->npc[j].h,box->npc[j].y - box->npc[j].h,box->npc[j].h*2, box->npc[j].h*2)))
                    {

                        box->shot[i].h = box->shot[i].h * 7;

                        for(int jjj = 0; jjj < box->MAX_NPC; jjj++)
                        {
                            if((QRect(a - box->shot[i].h, b - box->shot[i].h, box->shot[i].h*2, box->shot[i].h*2))
                                    .intersects(QRect(box->npc[jjj].x - box->npc[jjj].h,box->npc[jjj].y - box->npc[jjj].h,box->npc[jjj].h*2, box->npc[jjj].h*2)))
                            {
                                qDebug() << "die";
                                box->npc[jjj].active = false;
                                box->npc[jjj].h = 0;
                                destroy_npc++;
                                box->score+=10;

                            }
                        }

                        qDebug() << "destroy npc" << destroy_npc;

                        //box->shot[i].active = false;
                        box->shot[i].x = box->shot[i].x;
                        box->shot[i].y = box->shot[i].y;

                        return;

                    }
                }
                else //другие обычные патроны
                {
                if((QRect(a - box->shot[i].h, b - box->shot[i].h, box->shot[i].h*2, box->shot[i].h*2))
                        .intersects(QRect(box->npc[j].x - box->npc[j].h,box->npc[j].y - box->npc[j].h,box->npc[j].h*2, box->npc[j].h*2)))
                {

                    qDebug() << "die";
                    box->npc[j].active = false;
                    box->npc[j].h = 0;

                    box->shot[i].active = false;
                    destroy_npc++;
                    box->score+=10;
                    qDebug() << "destroy npc" << destroy_npc;
                    return;

                }
                }
            }
        }
    }
}


SingleMotor::SingleMotor(QObject *parent) :
    QObject(parent)
{

    initObjects();

}

void SingleMotor::start()
{


    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),SLOT(repeatAction()));
    timer->setInterval(100);
    timer->start();
}

void SingleMotor::myActionFromMapping_sl(My_action a)
{
    switch(a)
    {
    case UP:
        //box->my.y -= STEP_MY;
        stepObject(box->my.x,box->my.y,box->my.angle,-STEP_MY);
        break;

    case DOWN:
        stepObject(box->my.x,box->my.y,box->my.angle,STEP_MY);
        break;

    case LEFT:

        bendObject(box->my.x,box->my.y,box->my.angle, true);
        //box->my.angle -= 2;
        break;

    case RIGHT:
        bendObject(box->my.x,box->my.y,box->my.angle, false);
        break;

    case SHOT:
        birthShot();
        break;


    case CHANGE_WEAPON:
        if(box->my.type_weapon == 4)
            box->my.type_weapon = 0;
        box->my.type_weapon++;
        qDebug() << "weapon change" << box->my.type_weapon;
        break;


    }
}
