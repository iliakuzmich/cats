#ifndef BOSS_H
#define BOSS_H

#include <QObject>
#include <QTimer>
#include <QMovie>

class Boss : public QObject
{
    Q_OBJECT
public:
    explicit Boss(QObject *parent = nullptr);
    int hp = 100;
    int HP;
    int damag = 10;
    bool is_visible = 0;
    int xspeed = 6;
    int yspeed = 3;
    QTimer *xtimer;
    QTimer *ytimer;
    QTimer *switchdirx;
    QTimer *switchdiry;
    bool is_alive = 1;
    int x = 580;
    int y = 450;

    QMovie* gif;

    void stoptimer();
    void golr();
    void goud();
    void swdirx();
    void swdiry();

};

#endif // BOSS_H
