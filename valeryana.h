#ifndef VALERYANA_H
#define VALERYANA_H

#include "cat.h"
#include <QObject>
#include <QTimer>
#include <random>

class valeryana: public QObject
{
    Q_OBJECT

public:
    explicit valeryana(QObject *parent = 0);
    void is_colide(Cat cat);
    void set_pos();
    int a[3][2] = {{100, 100},{250,250},{500,500}};
    int x;
    int y;
    QTimer *valtimer;
signals:
    void doXp();

};

#endif // VALERYANA_H
