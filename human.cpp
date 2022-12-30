#include "human.h"

human::human(QObject *parent)
    : QObject{parent}
{
    timer = new QTimer;
    //timer->start(500);
    glrtimer = new QTimer;
    //glrtimer->start(40);
    stimer  = new QTimer;
    connect(stimer, &QTimer::timeout, this, &human::gt);
    connect(glrtimer, &QTimer::timeout, this, &human::golr);
    jtimer = new QTimer;
    connect(jtimer, &QTimer::timeout, this, &human::jump);

    gif = new QMovie(":/res/img/h2.gif");
    gif->start();
}

bool human::is_scared()
{
    int i = rand() % 5;
    if (i > 1){  // завязать на сложность, чем она выше - тем выше шанс испугатьсяж
        return 0;
    }
    return 1;
}

void human::golr()
{
    x += speed;
    if (x == 1000 && y >= 0 && y <= 350){
        y = 570;
        x = 0;
    }
    if (x > -10 && x < -1 && y <= 800 && y >= 360){
        y = 200;
        x = 1000;
    }
    if (x == 300 && y >= 500){
        fill();
        stimer->start(2000);
        gif = new QMovie(":/res/img/h1.gif");
            gif->start();
        speed *= -1;
        k = 1;
        glrtimer->stop();
    }
    if (x == 200 && y <= 200){
        stimer->start(2000);
        gif = new QMovie(":/res/img/h1.gif");
        gif->start();
        speed *= -1;
        k = 0;
        glrtimer->stop();
    }
}

void human::jump(){
    glrtimer->stop();
    y -= jspeed;
    jspeed -= 1;
    if (jspeed == -5){
        jspeed = 5;
        jtimer->stop();
        stimer->start(1000);
    }
}

void human::gt()
{
    glrtimer->start(40);
    stimer->stop();
    if(k == 0){
        gif = new QMovie(":/res/img/h2.gif");
        gif->start();
    }
    if(k == 1){
        gif = new QMovie(":/res/img/h3.gif");
            gif->start();
    }
}

void human::fill()
{
    is_empt = 0;
}

