#include "Dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    w = this;
    resize(500,500);
    //QObject::connect(mapping,SIGNAL(myActi))
    single_game = new QPushButton("Single game",this);
    single_game->setGeometry(200,200,100,100);
    connect(single_game,SIGNAL(clicked()),SLOT(singleGame_sl()));
    single_game->show();

}

void Dialog::showMenu(bool b)
{
    if(b == false)
        single_game->hide();
}

Dialog::~Dialog()
{

}

void Dialog::singleGame_sl()
{
    this->close();
    //showMenu(false);


    mapping = new Mapping;

    mapping->show();

    single_motor = new SingleMotor;
    //mapping->show();
    //resize(800,800);



    connect(single_motor,SIGNAL(toMapping_sig(Box*)),mapping,SLOT(recvMotor_sl(Box*)));
    connect(mapping,SIGNAL(myActionToMotor_sig(My_action)),single_motor,SLOT(myActionFromMapping_sl(My_action)));


    single_motor->start();
    repaint();


    //connect()
}
