#include "enemy.h"

enemy::enemy(QObject *parent) :
    QObject(parent)
{
    x = 600;
    y = 100;
    hp = 100;
    damag = 5;
    is_visible = 1;
    HP = hp;

    golrtimer = new QTimer();
    swithdirtimer = new QTimer();


    gif = new QMovie();

    connect(golrtimer, &QTimer::timeout, this, &enemy::go);
    connect(swithdirtimer, &QTimer::timeout, this, &enemy::chdir);

    golrtimer->start(40);
    swithdirtimer->start(rand() % 1000 + 2000);
}

enemy::enemy(enemy const &a)
{
    x= a.x;
    y = a.y;
    hp = a.hp;
    HP = hp;
    damag = a.damag;
    speed = a.speed;
    is_visible = a.is_visible;
    is_checkble = a.is_checkble;

    golrtimer = new QTimer();
    swithdirtimer = new QTimer();


    connect(golrtimer, &QTimer::timeout, this, &enemy::go);
    connect(swithdirtimer, &QTimer::timeout, this, &enemy::chdir);

    golrtimer->start(40);
    swithdirtimer->start(rand() % 1000 + 2000);
}

enemy::~enemy()
{

}

void enemy::go()
{
    x += speed;
}

void enemy::set_all(int X, int Y, int Hp, int D, int S, bool C)
{
    x = X;
    y = Y;
    hp = Hp;
    damag = D;
    speed = S;
    is_checkble = C;
}

void enemy::chdir()
{
    speed *= -1;
}

void enemy::stopTimers()
{
    golrtimer->stop();
    swithdirtimer->stop();
}

void enemy::die()
{
    hp = 0;
    is_checkble = 0;
    is_visible = 0;
}


void enemy::do_invis()
{
    is_visible = 0;
}
