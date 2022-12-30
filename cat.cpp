#include "cat.h"

Cat::Cat(QObject *parent) :
    QObject(parent)
{
    x = 100;
    y = 100;
    angle = 0;
    steps = 1;
    countForSteps = 0;
    k = 4;

    cXP = 100;
    hXP = 150;

    jtimer = new QTimer();
    Cat::connect(jtimer, &QTimer::timeout, this, &Cat::jump);

    mltimer = new QTimer();
    Cat::connect(mltimer, &QTimer::timeout, this, &Cat::go_left);

    mrtimer = new QTimer();
    Cat::connect(mrtimer, &QTimer::timeout, this, &Cat::go_right);

    gtimer = new QTimer;
    Cat::connect(gtimer, &QTimer::timeout, this, &Cat::gravity);
    //gtimer->start(40);

    atacktimer = new QTimer();
    //atacktimer->start(1000);
}

Cat::~Cat()
{

}

void Cat::regen()
{
    K += 1;
    K %= 5;
    if(K == 2)
        if(hXP < 100)
            hXP += 1;
}

void Cat::getHDamage(int d)
{
    hXP -= d;
}

void Cat::fillXP(){
    cXP = 100;
   // hXP = 100;
}

void Cat::fillcxp()
{
    if (cXP > 0)
        cXP = 100;
}

bool Cat::is_colide_b(block& a)
{
    if(y >= a.y - 26 && y <= a.y - 3 && x + 13 >= a.x && x <= a.x + 10){
        return 1;
    }
    else
    {
        return 0;
    }
}

bool Cat::is_colide_b(platform& a)
{
    if(y >= a.y - 26 && y <= a.y - 3 && x + 13 >= a.x && x <= a.x + 10){
        return 1;
    }
    else
    {
        return 0;
    }
}

bool Cat::is_colide_u(block &a)
{
    if(y >= a.y && y <= a.y + 20 && x + 10 >= a.x && x <= a.x + 10){
        return 1;
    }
    else
    {
        return 0;
    }
}

int t(int Px, int Py, int Ax, int Ay, int Bx, int By)
{
    return (Bx - Ax) * (Py - Ay) - (By - Ay) * (Px - Ax);
}

bool Cat::is_colide_r(block& a)
{
    int v = t(a.x, a.y, x + 15, y , x + 25, y);
    int b = t(a.x, a.y, x + 25, y , x + 25, y + 25);
    int c = t(a.x, a.y, x + 25, y + 25 , x + 15, y + 25);
    int d = t(a.x, a.y, x + 15, y + 25 , x + 15, y);
    if (((v < 0 && b < 0 && c < 0 && d < 0) || (v > 0 && b > 0 && c > 0 && d > 0)) ){
        return 1;
    }
    else{
        return 0;
    }
}

bool Cat::is_colide_l(block& a)
{
    int v = t(a.x + 20, a.y, x, y , x + 10, y);
    int b = t(a.x + 20, a.y, x + 10, y , x + 10, y + 25);
    int c = t(a.x + 20, a.y, x + 10, y + 25 , x, y + 25);
    int d = t(a.x + 20, a.y, x, y + 25 , x, y);
    if (((v < 0 && b < 0 && c < 0 && d < 0) || (v > 0 && b > 0 && c > 0 && d > 0)) ){
        return 1;
    }
    else{
        return 0;
    }
}


void Cat::stopjump()
{
    gtimer->start(40);
    jtimer->stop();
    is_jump_now = 0;
    is_pos_jump = 0;
    jumpspeed = 18;
}

void Cat::go_right()
{
    x += speed;
}

void Cat::go_left(){
    x -= speed;
}

void Cat::jump(){
    is_jump_now = 1;
    gtimer->stop();
    y -= jumpspeed;
    jumpspeed -= 1;
    if (jumpspeed <= 0){
        stopjump();
    }
}

void Cat::gravity()
{
        y += k;
}

QRectF Cat::boundingRect() const
{
    return QRectF(-25, -40, 50, 80);
}
