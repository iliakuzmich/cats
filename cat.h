#ifndef CAT_H
#define CAT_H

#include <QPainter>
#include <QObject>
#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsItem>

#include "block.h"

class Cat :public QObject
{
    Q_OBJECT

public:
    explicit Cat(QObject *parent = 0);
    ~Cat();

    int koh = 0;

    int x;
    int y;
    int speed = 7;
    int jumpspeed = 19;
    bool is_jump_now = 0;
    bool is_pos_jump = 0;
    QTimer *jtimer;
    QTimer *mltimer;
    QTimer *mrtimer;
    QTimer* atacktimer;
    QTimer* gtimer;
    //QTimer *timer;
    int k;
    int K = 0;

    void regen();

    int cXP = 100;
    int hXP = 150;

    void getHDamage(int d);
    void atack();
    bool is_colide_b(block& a);
    bool is_colide_b(platform& a);
    bool is_colide_u(block& a);
    bool is_colide_l(block& a);
    bool is_colide_r(block& a);
    void stopjump();
    void getHD(int d);

signals:
    void GO();
public:
    void go_right();
    void go_left();

public slots:
    void gravity();
    void jump();
    void fillXP();
    void fillcxp();
    //void getCD(int d);

protected:
    QRectF boundingRect() const;

private:
    qreal angle;
    int steps;
    int countForSteps;

};

#endif // CAT_H
