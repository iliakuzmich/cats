#include "valeryana.h"

valeryana::valeryana(QObject *parent):QObject(parent)
{
    set_pos();
    valtimer = new QTimer;
    valeryana::connect(valtimer, &QTimer::timeout, this, &valeryana::set_pos);
    //valtimer->start(10 * 1000);
}

void valeryana::set_pos()
{
    int i = rand() % 3;
    x = a[i][0];
    y = a[i][1];
}
