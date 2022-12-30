#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QMovie>

class enemy: public QObject
{
    Q_OBJECT
public:
    int x;
    int y;
    explicit enemy(QObject *parent = 0);
    enemy(enemy const &a);
    ~enemy();
    void pause();
    int hp;
    int HP;
    int damag;
    int speed;
    bool is_visible;
    bool is_checkble;

    QMovie* gif;

    QTimer *golrtimer;
    QTimer *swithdirtimer;

    void go();

    void set_all(int X, int Y, int Hp, int D, int S, bool C);

    void chdir();
    void stopTimers();
    void die();
    //void atack_cat();
    //void atack_houme();

signals:
//    void signalCheckGameOver();
//    void acat(int d);
//    void ahoume(int d);

public slots:
    void do_invis();

//protected:
//    QRectF boundingRect() const;

private:
//    int countAttack; //счетчик для периодичности атак
//    QGraphicsItem *target; //цель которую атаковать

private slots:
//    void slotGameTimer();
};
#endif // ENEMY_H
