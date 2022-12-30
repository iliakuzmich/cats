#include "boss.h"

Boss::Boss(QObject *parent)
    : QObject{parent}
{
    xtimer = new QTimer();
    ytimer = new QTimer();
    switchdirx = new QTimer();
        switchdiry = new QTimer();

    HP = hp;

    Boss::connect(xtimer, &QTimer::timeout, this, &Boss::golr);
    Boss::connect(ytimer, &QTimer::timeout, this, &Boss::goud);
    Boss::connect(switchdirx, &QTimer::timeout, this, &Boss::swdirx);
    Boss::connect(switchdiry, &QTimer::timeout, this, &Boss::swdiry);

    gif = new QMovie(":/res/img/1.gif");
    gif->start();

    xtimer->start(40);
    ytimer->start(50);
    switchdirx->start(3000);
    switchdiry->start(3500);

}

void Boss::golr()
{
    x += xspeed;
}

void Boss::goud(){
    y += yspeed;
}

void Boss::swdirx()
{
    xspeed *= -1;
}

void Boss::swdiry()
{
    yspeed *= -1;
}
