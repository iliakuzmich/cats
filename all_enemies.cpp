#include "all_enemies.h"

all_enemies::all_enemies(QObject *parent)
    : QObject{parent}
{
    ahtimer = new QTimer();
    //ahtimer->start(5000);
    boss = new Boss();
    spawntimer = new QTimer();
    all_enemies::connect(spawntimer, &QTimer::timeout, this, &all_enemies::spawn);
    //spawntimer->start(10000);
}

void all_enemies::spawn()
{
    if(boss->hp > 0){
        int k = rand() % 10;
        if (en[k].hp < 1){
            en[k].hp = rand() % 100 + 10;
            en[k].set_all(en[k].x, en[k].y, rand() % 100 + 100, rand()%5 * 7 + 5, rand()%4, 0);
            en[k].HP = en[k].hp;
            if (en[k].speed == 3){
                en[k].is_checkble = 1;
            }
        }
        if (en[k].speed == 0)
                en[k].gif = new QMovie(":/res/img/2.gif");
        if (en[k].speed == 1)
                en[k].gif = new QMovie(":/res/img/3.gif");
        if (en[k].speed == 2)
                en[k].gif = new QMovie(":/res/img/4.gif");
        if (en[k].speed == 3)
                en[k].gif = new QMovie(":/res/img/5.gif");

        en[k].gif->start();
    }
}

void all_enemies::calckHD()
{
    D = 0;
    for (auto ele = en.begin(); ele != en.end(); ele++){
        if(ele->hp > 0)
            D += ele->damag;
    }
}
