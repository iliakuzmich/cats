#ifndef HUMAN_H
#define HUMAN_H

#include <QTimer>
#include <QObject>
#include <QMovie>

class human : public QObject
{
    Q_OBJECT
public:
    explicit human(QObject *parent = nullptr);
    int x = 200;
    int y = 200;
    bool is_scared();
    int speed = 5;
    void golr();
    void jump();
    int jspeed = 5;
    QTimer* timer;
    QTimer* jtimer;
    QTimer* glrtimer;
    QTimer* stimer;
    void gt();

    int k = 0;

    QMovie* gif;

    void fill();

    int bx = 400;
    int by = 650;
    bool is_empt = 1;
};

#endif // HUMAN_H
